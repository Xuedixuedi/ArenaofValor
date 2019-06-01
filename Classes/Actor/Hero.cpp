#include "Hero.h"
#include "Component/Equipment.h"
#include "Component/ExpComponent.h"
#include "Component/StateComponent.h"
#include "Component/Record.h"
#include "Component/Bonus.h"
#include "Scene/HelloWorldScene.h"
#include <set>


Hero* Hero::create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	Hero* hero = new(std::nothrow)Hero;
	if (hero && hero->init(combatScene, camp, heroName, attackMode))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}



bool Hero::init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	initHeroData(combatScene, heroName, camp, attackMode);
	initHealthComp(heroName);
	initMagicComp(heroName);
	initExpComp();
	initRecordComp();

	return true;
}

bool Hero::initHeroData(HelloWorld* combatScene, std::string heroName, ECamp camp, EAttackMode attackMode)
{
	ValueMap value = FileUtils::getInstance()->getValueMapFromFile("A:\\major\\exedir\\wzry\\Data\\HeroDataAtEachLevel.plist");
	_heroDataAtEachLevel = value.at(heroName).asValueMap();
	_heroData= (FileUtils::getInstance()->getValueMapFromFile("A:\\major\\exedir\\wzry\\Data\\HeroData.plist"))[heroName].asValueMap();
	_commonData = FileUtils::getInstance()->getValueMapFromFile("A:\\major\\exedir\\wzry\\Data\\CommonData.plist");
	_skillData = (FileUtils::getInstance()->getValueMapFromFile("A:\\major\\exedir\\wzry\\Data\\SkillData.plist"))[heroName].asValueMap();

	_combatScene = combatScene;
	setTexture(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.c_str(),heroName.c_str()));
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	_heroName = heroName;
	_camp = camp;
	_attackMode = attackMode;
	_alreadyDead = false;
	_attackRadius = _attackMode == EAttackMode::MELEE ? DEFAULT_ATTACK_RADIUS_MELEE : DEFAULT_ATTACK_RADIUS_REMOTE;
	_lastAttackTime = 0.f;
	_direction = EDirection::LEFT;
	_standingAngle = 0.f;
	_moveSpeed = _heroData["MovingSpeed"].asInt();
	_lastTimeDead = 0.f;
	_lastTimeReborn = 0.f;
	_minAttackInterval = MIN_ATTACK_INTERVAL;
	_multipleLastTo = 0.f;
	_silenceLastTo = 0.f;
	_vertigoLastTo = 0.f;
	_resurgenceTime = 0.f;

	_defense = _heroDataAtEachLevel["Armor"].asValueVector().at(1).asInt();
	_attack = _heroDataAtEachLevel["BaseDamage"].asValueVector().at(1).asInt();
	_magicDefense = _heroDataAtEachLevel["MagicDefense"].asValueVector().at(1).asInt();

	_calmTime_1 = _skillData["CD"].asValueVector().at(1).asValueVector().at(0).asFloat();
	_calmTime_2 = _skillData["CD"].asValueVector()[2].asValueVector()[0].asFloat();
	_calmTime_3 = _skillData["CD"].asValueVector()[3].asValueVector()[0].asFloat();

	_magicConsume_1 = _skillData["MPConsume"].asValueVector()[1].asValueVector()[0].asFloat();
	_magicConsume_2 = _skillData["MPConsume"].asValueVector()[2].asValueVector()[0].asFloat();
	_magicConsume_3 = _skillData["MPConsume"].asValueVector()[3].asValueVector()[0].asFloat();

	_skillLevel_1 = _skillLevel_2 = _skillLevel_3 = 0;
	_lastSkillTime_1 = _lastSkillTime_2 = _lastSkillTime_3 = 0.f;

	_skillPoint = 0;

	return true;
}

bool Hero::initHealthComp(std::string heroName)
{
	auto defaultRecoverRate = _heroData["HPRecoverRate"].asInt();
	auto defaultMaxHealth = _heroDataAtEachLevel["HP"].asValueVector().at(1).asInt();
	_healthComp = StateComponent::create(EStateType::HEALTH, defaultMaxHealth, defaultRecoverRate);

	auto position = getPosition();
	auto size = getBoundingBox().size;

	_healthComp->setScaleX(0.9);
	_healthComp->setScaleY(2.0);
	_healthComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_healthComp->setPosition(position + Vec2(size.width / 2, size.height - 20));
	addChild(_healthComp);

	return true;
}

bool Hero::initMagicComp(std::string heroName)
{	
	auto defaultRecoverRate = _heroData["MPRecoverRate"].asInt();
	auto defaultMaxMagic = _heroDataAtEachLevel["MP"].asValueVector().at(1).asInt();
	_magicComp = StateComponent::create(EStateType::MAGIC, defaultMaxMagic, defaultRecoverRate);

	auto position = getPosition();
	auto size = getBoundingBox().size;

	_magicComp->setScaleX(0.9);
	_magicComp->setScaleY(1.0);
	_magicComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_magicComp->setPosition(position + Vec2(size.width / 2, size.height - 35));
	addChild(_magicComp);

	return true;
}

bool Hero::initExpComp()
{
	_expComp = ExpComponent::create(_commonData["ExpNeeded"].asValueVector().at(1).asInt());
	_expComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	auto healthCompSize = _healthComp->getBoundingBox().size;
	auto position = (_healthComp->getPosition() + _magicComp->getPosition()) / 2;
	_expComp->setPosition(position + Vec2(-1 * healthCompSize.width / 2, 0));
	addChild(_expComp);

	return true;
}

bool Hero::initRecordComp()
{
	_recordComp = Record::create();

	return true;
}

bool Hero::attack()
{
	return false;
}

void Hero::takeDamage(EDamageType damageType, INT32 damage, Actor* instigator)
{
	INT32 actualDamage;

	if (damageType == EDamageType::PHYSICS_DAMAGE)
	{
		actualDamage = static_cast<INT32>((1.0 - 1.0 * _defense / (_defense + 602.f)) * damage);
	}
	else
	{
		actualDamage = static_cast<INT32>((1.0 - 1.0 * _magicDefense / (_magicDefense + 602.f)) * damage);
	}

	_healthComp->changeStateBy(-1 * actualDamage);
	_lastAttackFrom = instigator;

	auto damageByHero = dynamic_cast<Hero*>(instigator);
	if (damageByHero && _healthComp->getCurrentState() > 0)
	{
		_causeDamageActors.insert(GetCurrentTime() / 1000.f, damageByHero);
	}
	if (_healthComp->getCurrentState() <= 0)
	{
		die();
	}
}

void Hero::die()
{
	setVisible(false);
	auto nowTime = GetCurrentTime() / 1000.f;
	_alreadyDead = true;
	_lastTimeDead = nowTime;
	_resurgenceTime = 6 + 4 * getExpComp()->getLevel() + nowTime;
	removeAllBuff();

	_recordComp->updateDeath();

	auto money = getRecordComp()->getMoney();
	getRecordComp()->setMoney(money * 2 / 3);

	auto expForKill = (FileUtils::getInstance()->getValueMapFromFile("A:\\major\\exedir\\wzry\\Data\\CommonData.plist"))["ExpNeeded"].asValueVector()[getExpComp()->getLevel()].asInt();
	auto goldForKill = money / 3 + getExpComp()->getLevel() * 80;

	auto lastAttackHero = dynamic_cast<Hero*>(_lastAttackFrom);
	if (lastAttackHero)
	{
		lastAttackHero->getRecordComp()->addMoney(goldForKill / 3);
		goldForKill = goldForKill * 2 / 3;
		lastAttackHero->getRecordComp()->updateKill();

		if (!lastAttackHero->getAlreadyDead())
		{
			lastAttackHero->addExp(expForKill / 3);
			expForKill = expForKill * 2 / 3;
		}

		std::set<Hero*> assistHeroes;
		for (auto& i : _causeDamageActors)
		{
			if (i.first + 2 >= nowTime && i.second != lastAttackHero && assistHeroes.find(i.second) == assistHeroes.end())
			{
				i.second->getRecordComp()->updateAssist();
				assistHeroes.insert(i.second);
			}
		}
		assistHeroes.clear();
	}
	else
	{
		std::set<Hero*> assistHeroes;
		for (auto& i : _causeDamageActors)
		{
			if (i.first + 2 >= nowTime && assistHeroes.find(i.second) == assistHeroes.end())
			{
				i.second->getRecordComp()->updateAssist();
				assistHeroes.insert(i.second);
			}
		}
		assistHeroes.clear();
	}

	_causeDamageActors.clear();

	INT32 heroCount = 0;
	for (auto& i : _combatScene->_heroes)
	{
		if (!i->getAlreadyDead() && i->getCamp() != _camp && i->getPosition().distance(getPosition()) <= VISION_RADIUS)
		{
			++heroCount;
		}
	}
	if (heroCount == 0)
	{
		return;
	}

	auto goldForEachHero = goldForKill / heroCount;
	auto expForEachHero = expForKill / heroCount;
	for (auto& i : _combatScene->_heroes)
	{
		if (!i->getAlreadyDead() && i->getCamp() != _camp && i->getPosition().distance(getPosition()) <= VISION_RADIUS)
		{
			i->getRecordComp()->addMoney(goldForEachHero);
			i->addExp(expForEachHero);
		}
	}
}

void Hero::removeAllBuff()
{
	_vertigoLastTo = 0.f;
	_silenceLastTo = 0.f;
	_multipleLastTo = 0.f;

	for (auto& i : _allBuff)
	{
		_magicComp->changeMaxBy(-1 * i->getMP());
		_magicComp->changeRecoverRate(-1 * i->getMPRevoer());
		_attack -= i->getAttack();
		_defense -= i->getDefense();
		_magicDefense -= i->getMagicDefense();
		_healthComp->changeMaxBy(-1 * i->getHP());
		_healthComp->changeMaxBy(-1 * i->getHPRecover());
		_minAttackInterval += i->getAttackInterval();
	}

	_allBuff.clear();
}

void Hero::removeBuff(Buff* buff)
{
	MovingActor::removeBuff(buff);

	_magicComp->changeMaxBy(-1 * buff->getMP());
	_magicComp->changeRecoverRate(-1 * buff->getMPRevoer());
}

void Hero::takeBuff(Buff* buff)
{

	MovingActor::takeBuff(buff);

	_magicComp->changeMaxBy(buff->getMP());
	_magicComp->changeRecoverRate(buff->getMPRevoer());
	
	auto buffType = buff->getBuffType();
	if (buffType == EBuffType::MULTIPLE)
	{
		_multipleLastTo = std::max(_multipleLastTo, buff->getEndTime());
	}
	else if (buffType == EBuffType::SILENCE)
	{
		_silenceLastTo = std::max(_silenceLastTo, buff->getEndTime());
	}
}

void Hero::skillLevelUp(INT32 skillNumber)
{
	--_skillPoint;
	switch (skillNumber)
	{
	case 1:
		++_skillLevel_1;
		_calmTime_1 = _skillData["CD"].asValueVector()[1].asValueVector()[_skillLevel_1].asFloat();
		_magicConsume_1 = _skillData["MPConsume"].asValueVector()[1].asValueVector()[_skillLevel_1].asFloat();
		break;
	case 2:
		++_skillLevel_2;
		_calmTime_2 = _skillData["CD"].asValueVector()[2].asValueVector()[_skillLevel_2].asFloat();
		_magicConsume_2 = _skillData["MPConsume"].asValueVector()[2].asValueVector()[_skillLevel_2].asFloat();
		break;
	case 3:
		++_skillLevel_3;
		_calmTime_3 = _skillData["CD"].asValueVector()[3].asValueVector()[_skillLevel_3].asFloat();
		_magicConsume_3 = _skillData["MPConsume"].asValueVector()[3].asValueVector()[_skillLevel_3].asFloat();
		break;
	default:
		break;
	}
}

void Hero::castSkill_1()
{
}

void Hero::castSkill_1(Point mousePosition)
{
}

void Hero::castSkill_2(Point mousePosition)
{
}

void Hero::castSkill_3()
{
}

void Hero::castSkill_2()
{
}

void Hero::castSkill_3(Point point)
{
}

void Hero::reborn()
{
	_alreadyDead = false;
	_healthComp->changeStateBy(_healthComp->getMaxState());
	_magicComp->changeStateBy(_magicComp->getMaxState());
	setVisible(true);

	auto birthPlace = _camp == ECamp::BLUE ? BLUE_HERO_BIRTHPLACE : RED_HERO_BIRTHPLACE;
	setPosition(birthPlace);
}

void Hero::heroMove()
{
	auto nowTime = GetCurrentTime() / 1000.f;
	if (nowTime - _lastAttackTime > _minAttackInterval)
	{
		_isAttacking = false;
	}
	if (_isAttacking)
	{
		return;
	}

	if (nowTime <= _vertigoLastTo)
	{
		return;
	}

	EDirection oldDirection = _direction;

	updateDirection();
	if (_direction != oldDirection)
	{
		startAnimation();
	}

	setPosition(MyMath::calculatePositionDelta(_standingAngle, _moveSpeed) + getPosition());
}

void Hero::updateDirection()
{
	if (_standingAngle < MIN_DEGREE_IN_RAD || _standingAngle > 15 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%sright1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::RIGHT;
	}
	else if (_standingAngle < 3 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%supRight1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::UPRIGHT;
	}
	else if (_standingAngle < 5 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%sup1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::UP;
	}
	else if (_standingAngle < 7 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%supLeft1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::UPLEFT;
	}
	else if (_standingAngle < 9 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%sleft1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::LEFT;
	}
	else if (_standingAngle < 11 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%sdownRight1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::DOWNLEFT;
	}
	else if (_standingAngle < 13 * MIN_DEGREE_IN_RAD)
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%sdown1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::DOWN;
	}
	else
	{
		//setTexture(StringUtils::format("pictures//hero//%s//%sdownRight1.png", _heroName.getCString(), _heroName.getCString()));
		_direction = EDirection::DOWNRIGHT;
	}
}

void Hero::addExp(INT32 delta)
{
	if (_expComp->addExp(delta))
	{
		levelUp();
	}
}

void Hero::levelUp()
{
	auto newLevel = _expComp->getLevel();

	auto levelUpNeededExp = _commonData["ExpNeeded"].asValueVector().at(newLevel).asInt();
	_expComp->setLevelUpNeededExp(levelUpNeededExp);

	auto deltaHp = _heroDataAtEachLevel["HP"].asValueVector().at(newLevel).asInt() - _heroDataAtEachLevel["HP"].asValueVector().at(newLevel - 1).asInt();
	_healthComp->changeMaxBy(deltaHp);

	auto deltaMagic = _heroDataAtEachLevel["MP"].asValueVector().at(newLevel).asInt() - _heroDataAtEachLevel["MP"].asValueVector().at(newLevel - 1).asInt();
	_magicComp->changeMaxBy(deltaMagic);

	auto deltaArmor = _heroDataAtEachLevel["Armor"].asValueVector().at(newLevel).asInt() - _heroDataAtEachLevel["Armor"].asValueVector().at(newLevel - 1).asInt();
	_defense += deltaArmor;

	auto deltaMagicDefense = _heroDataAtEachLevel["MagicDefense"].asValueVector().at(newLevel).asInt() - _heroDataAtEachLevel["MagicDefense"].asValueVector().at(newLevel - 1).asInt();
	_magicDefense += deltaMagicDefense;

	auto deltaAttack= _heroDataAtEachLevel["BaseDamage"].asValueVector().at(newLevel).asInt() - _heroDataAtEachLevel["BaseDamage"].asValueVector().at(newLevel - 1).asInt();
	_attack += deltaAttack;

	++_skillPoint;
}

void Hero::stopMove()
{
	auto nowTime = GetCurrentTime() / 1000.f;
	if (nowTime - _lastAttackTime > _minAttackInterval)
	{
		_isAttacking = false;
	}
	if (_isAttacking)
	{
		return;
	}

	stopAllActions();

	switch (_direction)
	{
	case EDirection::DOWN :
		setTexture(StringUtils::format("pictures\\hero\\%s\\%sdown1.png",_heroName.getCString(),_heroName.getCString()));
		break;
	case EDirection::DOWNLEFT:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	case EDirection::DOWNRIGHT:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	case EDirection::LEFT:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	case EDirection::RIGHT:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%sright1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	case EDirection::UP:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%sup1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	case EDirection::UPLEFT:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%supLeft1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	case EDirection::UPRIGHT:
		setTexture(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", _heroName.getCString(), _heroName.getCString()));
		break;
	}

	_direction = EDirection::NODIR;
}

void Hero::startAnimation()
{
	stopAllActions();

	auto animation = Animation::create();

	switch (_direction)
	{
	case EDirection::DOWN:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveDown", _heroName.getCString()));
		break;
	case EDirection::DOWNLEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveDownLeft", _heroName.getCString()));
		break;
	case EDirection::DOWNRIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveDownRight", _heroName.getCString()));
		break;
	case EDirection::LEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveLeft", _heroName.getCString()));
		break;
	case EDirection::RIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveRight", _heroName.getCString()));
		break;
	case EDirection::UP:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveUp", _heroName.getCString()));
		break;
	case EDirection::UPLEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveUpLeft", _heroName.getCString()));
		break;
	case EDirection::UPRIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveUpRight", _heroName.getCString()));
		break;
	}

	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);

	auto animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

bool Hero::checkSkillStatus(INT32 skillNumber)
{
	auto nowTime = GetCurrentTime() / 1000.f;
	//眩晕状态和沉默状态下不可进行技能释放
	if (_vertigoLastTo >= nowTime || _silenceLastTo >= nowTime)
	{
		return false;
	}
	//检测是否习得技能并且不在技能冷却内
	switch (skillNumber)
	{
	case 1:
		if (_skillLevel_1 == 0 || _lastSkillTime_1 + _calmTime_1 >= nowTime || _magicComp->getCurrentState() < _magicConsume_1)
		{
			return false;
		}
		break;
	case 2:
		if (_skillLevel_2 == 0 || _lastSkillTime_2 + _calmTime_2 >= nowTime || _magicComp->getCurrentState() < _magicConsume_2)
		{
			return false;
		}
		break;
	case 3:
		if (_skillLevel_3 == 0 || _lastSkillTime_3 + _calmTime_3 >= nowTime || _magicComp->getCurrentState() < _magicConsume_3)
		{
			return false;
		}
		break;
	default:
		return false;
	}
	return true;
}

void Hero::playAttackAnimation()
{
	auto animation = Animation::create();
	switch (_direction)
	{
	case UP:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackUp", _heroName.getCString()));
		break;
	case DOWN:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackDown", _heroName.getCString()));
		break;
	case LEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackLeft", _heroName.getCString()));
		break;
	case RIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackRight", _heroName.getCString()));
		break;
	case UPLEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackUpLeft", _heroName.getCString()));
		break;
	case UPRIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackUpRight", _heroName.getCString()));
		break;
	case DOWNLEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackDownLeft", _heroName.getCString()));
		break;
	case DOWNRIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackDownRight", _heroName.getCString()));
		break;
	case NODIR:
		break;
	default:
		break;
	}
	animation->setDelayPerUnit(_minAttackInterval / 6);
	animation->setLoops(1);
	auto animate = Animate::create(animation);
	runAction(animate);
}


void Hero::updateAttackTarget(INT32 radius)
{
	INT32 minHealth = 10000000;
	Actor* tmpTarget = NULL;

	Vector<Hero*>& allHeroes = _combatScene->_heroes;
	Vector<Soldier*>& allSoldiers = _combatScene->_soldiers;
	Vector<Actor*>& allTowers = _combatScene->_towers;
	for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
	{
		if ((*it)->getHealthComp()->getCurrentState() < minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= radius)
		{
			minHealth = (*it)->getHealthComp()->getCurrentState();
			tmpTarget = *it;
		}
	}
	if (!tmpTarget)
	{
		for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
		{
			if ((*it)->getHealthComp()->getCurrentState() < minHealth)
			{
				if (_camp != (*it)->getCamp() && !(*it)->getAlreadyDead())
				{
					if ((*it)->getPosition().distance(this->getPosition()) <= radius)
					{
						minHealth = (*it)->getHealthComp()->getCurrentState();
						tmpTarget = *it;
					}
				}
			}
		}
	}
	if (!tmpTarget)
	{
		for (auto it = allTowers.begin(); it != allTowers.end(); ++it)
		{
			if ((*it)->getHealthComp()->getCurrentState() > minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= radius)
			{
				minHealth = (*it)->getHealthComp()->getCurrentState();
				tmpTarget = *it;
			}
		}
	}
	this->setAttackTarget(tmpTarget);
}

void Hero::updateAttackTarget()
{
	INT32 minHealth = 10000000;
	Actor* tmpTarget = NULL;

	Vector<Hero*>& allHeroes = _combatScene->_heroes;
	Vector<Soldier*>& allSoldiers = _combatScene->_soldiers;
	Vector<Actor*>& allTowers = _combatScene->_towers;
	for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
	{
		if ((*it)->getHealthComp()->getCurrentState() < minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= _attackRadius)
		{
			minHealth = (*it)->getHealthComp()->getCurrentState();
			tmpTarget = *it;
		}
	}
	if (!tmpTarget)
	{
		for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
		{
			if ((*it)->getHealthComp()->getCurrentState() < minHealth)
			{
				if (_camp != (*it)->getCamp() && !(*it)->getAlreadyDead())
				{
					if ((*it)->getPosition().distance(this->getPosition()) <= _attackRadius)
					{
						minHealth = (*it)->getHealthComp()->getCurrentState();
						tmpTarget = *it;
					}
				}
			}
		}
	}
	if (!tmpTarget)
	{
		for (auto it = allTowers.begin(); it != allTowers.end(); ++it)
		{
			if ((*it)->getHealthComp()->getCurrentState() > minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= _attackRadius)
			{
				minHealth = (*it)->getHealthComp()->getCurrentState();
				tmpTarget = *it;
			}
		}
	}
	this->setAttackTarget(tmpTarget);
}