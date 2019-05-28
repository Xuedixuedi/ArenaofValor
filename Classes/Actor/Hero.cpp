#include "Hero.h"
#include "Component/Equipment.h"
#include "Component/ExpComponent.h"
#include "Component/StateComponent.h"
#include "Component/Record.h"
#include "Component/Bonus.h"


Hero* Hero::create(ECamp camp, std::string heroName, EAttackMode attackMode, GameScene* scene)
{
	Hero* hero = new(std::nothrow)Hero;
	if (hero && hero->init(scene,camp, heroName, attackMode))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

void Hero::skillLevelUp(INT32 skillNumber)
{

}

void Hero::castSkill_1()
{

}

void Hero::castSkill_2(Point center)
{

}

void Hero::castSkill_3(Point point)
{

}

void Hero::updateAttackTarget()
{


}


bool Hero::init(GameScene* scene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	initHeroData(heroName, camp, attackMode);
	initHealthComp(heroName);
	initMagicComp(heroName);
	initExpComp();
	initRecordComp();
	_combatScene = scene;
	return true;
}	  

bool Hero::initHeroData(std::string heroName, ECamp camp, EAttackMode attackMode)
{
	ValueMap value = FileUtils::getInstance()->getValueMapFromFile("Data\\HeroDataAtEachLevel.plist");
	ValueMap heroDataAtEachLevel = value.at(heroName).asValueMap();
	ValueMap heroData= (FileUtils::getInstance()->getValueMapFromFile("Data\\HeroData.plist"))[heroName].asValueMap();

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
	_moveSpeed = heroData["MovingSpeed"].asInt();
	_lastTimeDead = 0.f;
	_lastTimeReborn = 0.f;

	_defense = heroDataAtEachLevel["Armor"].asValueVector().at(1).asInt();
	_attack = heroDataAtEachLevel["BaseDamage"].asValueVector().at(1).asInt();
	_magicDefense = heroDataAtEachLevel["MagicDefense"].asValueVector().at(1).asInt();

	return true;
}

bool Hero::initHealthComp(std::string heroName)
{
	ValueMap heroDataAtEachLevel = (FileUtils::getInstance()->getValueMapFromFile("Data\\HeroDataAtEachLevel.plist"))[heroName].asValueMap();
	ValueMap heroData = (FileUtils::getInstance()->getValueMapFromFile("Data\\HeroData.plist"))[heroName].asValueMap();

	auto defaultRecoverRate = heroData["HPRecoverRate"].asInt();
	auto defaultMaxHealth = heroDataAtEachLevel["HP"].asValueVector().at(1).asInt();
	_healthComp = StateComponent::create(EStateType::HEALTH, defaultMaxHealth, defaultRecoverRate);

	auto position = getPosition();
	auto size = getBoundingBox().size;

	_healthComp->setScaleX(0.9);
	_healthComp->setScaleY(1.4);
	_healthComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_healthComp->setPosition(position + Vec2(size.width / 2, size.height));
	addChild(_healthComp);

	return true;
}

bool Hero::initMagicComp(std::string heroName)
{
	ValueMap heroDataAtEachLevel = (FileUtils::getInstance()->getValueMapFromFile("Data\\HeroDataAtEachLevel.plist"))[heroName].asValueMap();
	ValueMap heroData = (FileUtils::getInstance()->getValueMapFromFile("Data\\HeroData.plist"))[heroName].asValueMap();
	
	auto defaultRecoverRate = heroData["MPRecoverRate"].asInt();
	auto defaultMaxMagic = heroDataAtEachLevel["MP"].asValueVector().at(1).asInt();
	_magicComp = StateComponent::create(EStateType::MAGIC, defaultMaxMagic, defaultRecoverRate);

	auto position = getPosition();
	auto size = getBoundingBox().size;

	_magicComp->setScaleX(0.9);
	_magicComp->setScaleY(0.7);
	_magicComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_magicComp->setPosition(position + Vec2(size.width / 2, size.height - 11));
	addChild(_magicComp);

	return true;
}

bool Hero::initExpComp()
{
	auto levelUpNeededExp = (FileUtils::getInstance()->getValueMapFromFile("Data\\CommonData.plist"))["ExpNeeded"].asValueVector().at(1);
	_expComp = ExpComponent::create(levelUpNeededExp.asInt());
	_expComp->setScale(0.7);
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


bool Hero::levelUp()
{
	return false;
}


bool Hero::die()
{
	return false;
}

bool Hero::attack()
{


	return false;
}

void Hero::takeBuff(Buff* buff)
{
	this->getAllBuff().pushBack(buff);
	_attack += buff->getAttack();
	_defense += buff->getDefense();
	_magicDefense += buff->getMagicDefense();
	_healthComp->changeMaxBy(buff->getHP());
	_magicComp->changeMaxBy(buff->getMP());
	_healthComp->changeRecoverRate(buff->getHPRecover());
	_magicComp->changeRecoverRate(buff->getMPRevoer());
	_moveSpeed += buff->getMoveSpeed();
	_minAttackInterval -= buff->getAttackInterval();

}

void Hero::reborn()
{
}

void Hero::takeDamage(float damge, Actor* instigator)
{
}

void Hero::heroMove()
{
	EDirection oldDirection = _direction;

	updateDirection();
	if (_direction != oldDirection)
	{
		startAnimation();
	}
	auto position = getPosition();
	setPosition(position + Vec2(cos(_standingAngle) * _moveSpeed / 60, sin(_standingAngle) * _moveSpeed / 60));
}

void Hero::updateDirection()
{
	if (_standingAngle < MIN_DEGREE_IN_RAD || _standingAngle > 15 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::RIGHT;
	}
	else if (_standingAngle < 3 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::UPRIGHT;
	}
	else if (_standingAngle < 5 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::UP;
	}
	else if (_standingAngle < 7 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::UPLEFT;
	}
	else if (_standingAngle < 9 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::LEFT;
	}
	else if (_standingAngle < 11 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::DOWNLEFT;
	}
	else if (_standingAngle < 13 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::DOWN;
	}
	else
	{
		_direction = EDirection::DOWNRIGHT;
	}
}

void Hero::stopMove()
{
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