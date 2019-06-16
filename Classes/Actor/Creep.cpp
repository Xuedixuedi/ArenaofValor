#include "Creep.h"
#include "Component/StateComponent.h"
#include "Scene/HelloWorldScene.h"
#include "Actor/Hero.h"
#include "Component/Record.h"

Creep* Creep::create(HelloWorld* combatScene, const std::string& creepName)
{
	auto creep = new(std::nothrow)Creep;
	if (creep && creep->init(combatScene, creepName))
	{
		creep->autorelease();
		return creep;
	}
	CC_SAFE_DELETE(creep);
	return nullptr;
}

bool Creep::init(HelloWorld* combatScene, const std::string& creepName)
{
	if (!Sprite::init())
	{
		return false;
	}

	initData(combatScene, creepName);
	initHealthComp();

	return true;
}

void Creep::initData(HelloWorld* combatScene, const std::string& creepName)
{
	_combatScene = combatScene;
	_creepName = creepName;

	if (creepName == "lion")
	{
		setTexture("pictures/creeps/lion/lionDown1.png");
		_birthPlace = LION_BIRTHPLACE;
	}
	else if (creepName == "tiger")
	{
		setTexture("pictures/creeps/tiger/tigerDown1.png");
		_birthPlace = TIGER_BIRTHPLACE;
	}
	else
	{
		setTexture("pictures/creeps/pig/pigDown1.png");
		_birthPlace = PIG_BIRTHPLACE;
	}

	_attackMode = EAttackMode::MELEE;
	_camp = ECamp::MID;
	_defense = SOLDIER_ARMOR;
	_attack = SOLDIER_ATTACK;
	_attackRadius = DEFAULT_ATTACK_RADIUS_MELEE;
	_alreadyDead = false;
	_magicDefense = SOLDIER_MAGIC_DEFENSE;
	_lastAttackTime = 0.f;
	_moveSpeed = SOLDIER_MOVE_SPEED;
	_isMovingBack = false;
	_instigator = nullptr;
	_minAttackInterval = MIN_ATTACK_INTERVAL;
	_isAttacking = false;
	_direction = EDirection::DOWN;
	_vertigoLastTo = 0.f;
	_standingAngle = 12 * MIN_DEGREE_IN_RAD;
}

void Creep::initHealthComp()
{
	if (_creepName != "pig")
	{
		_healthComp = StateComponent::create(EStateType::HEALTH, SOLDIER_HP * 2, 0);
	}
	else
	{
		_healthComp = StateComponent::create(EStateType::HEALTH, SOLDIER_HP * 4, 0);
	}
	auto position = getPosition();
	auto size = getBoundingBox().size;
	size.height *= 1.5;

	_healthComp->setScaleX(0.15);
	_healthComp->setScaleY(0.4);
	_healthComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_healthComp->setPosition(position + Vec2(size.width / 2, size.height * 2 / 3));
	addChild(_healthComp);
}

void Creep::updateState()
{
	auto nowTime = GetCurrentTime() / 1000.f;
	//	log("%f %f", nowTime, _vertigoLastTo);
	if (nowTime <= _vertigoLastTo)
	{
		stopAllActions();
		_direction = EDirection::NODIR;
		return;
	}

	if (nowTime - _lastAttackTime <= _minAttackInterval)
	{
		return;
	}

	if (getPosition().distance(_birthPlace) > VISION_RADIUS)
	{
		_isMovingBack = true;
	}
	if (_isMovingBack)
	{
		if (getPosition().distance(_birthPlace) < 20.f)
		{
			_isMovingBack = false;
			stopAllActions();
			setTexture(StringUtils::format("pictures/creeps/%s/%sDown1.png", _creepName.c_str(), _creepName.c_str()));
			return;
		}
		moveTo(_birthPlace);
		return;
	}

	if (_instigator)
	{
		if (_instigator->getAlreadyDead() || getPosition().distance(_instigator->getPosition()) > VISION_RADIUS)
		{
			_isMovingBack = true;
			_instigator = nullptr;
			return;
		}
	}

	if (_instigator)
	{
		if (getPosition().distance(_instigator->getPosition()) <= _attackRadius)
		{
			attack(_instigator);
		}
		else
		{
			moveTo(_instigator->getPosition());
		}
	}
}

void Creep::takeDamage(EDamageType damageType, INT32 damage, Actor* instigator)
{
	Actor::takeDamage(damageType, damage, instigator);

	if (!_instigator && !instigator->getAlreadyDead())
	{
		_instigator = instigator;
	}

}

void Creep::startAnimation()
{
	stopAllActions();

	auto animation = Animation::create();

	switch (_direction)
	{
	case EDirection::DOWN:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sDown", _creepName.c_str()));
		break;
	case EDirection::LEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sLeft", _creepName.c_str()));
		break;
	case EDirection::RIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sRight", _creepName.c_str()));
		break;
	case EDirection::UP:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sUp", _creepName.c_str()));
		break;
	}

	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);

	auto animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Creep::attack(Actor* attackTarget)
{
	stopAllActions();

	_isAttacking = true;
	_standingAngle = MyMath::getRad(getPosition(), attackTarget->getPosition());
	updateDirection();

	switch (_direction)
	{
	case UP:
		setTexture(StringUtils::format("pictures/creeps/%s/%sUp1.png", _creepName.c_str(), _creepName.c_str()));
		break;
	case DOWN:
		setTexture(StringUtils::format("pictures/creeps/%s/%sDown1.png", _creepName.c_str(), _creepName.c_str()));
		break;
	case LEFT:
		setTexture(StringUtils::format("pictures/creeps/%s/%sLeft1.png", _creepName.c_str(), _creepName.c_str()));
		break;
	case RIGHT:
		setTexture(StringUtils::format("pictures/creeps/%s/%sRight1.png", _creepName.c_str(), _creepName.c_str()));
		break;
	}

	auto nowTime = GetCurrentTime() / 1000.f;

	auto damage = Damage(_attack, this, attackTarget, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 10 * 3);
	_combatScene->_damages.push_back(damage);

	_lastAttackTime = nowTime;
}

void Creep::die()
{
	_alreadyDead = true;
	_allBuff.clear();

	auto goldForKill = 100;
	auto expForKill = 100;
	if (_creepName == "pig")
	{
		goldForKill += 100;
		expForKill += 100;
	}

	INT32 heroCount = 0;
	for (auto& i : _combatScene->_heroes)
	{
		if (!i->getAlreadyDead() && i->getCamp() != _camp && i->getPosition().distance(getPosition()) <= VISION_RADIUS)
		{
			++heroCount;
		}
	}

	auto lastAttackHero = dynamic_cast<Hero*>(_lastAttackFrom);
	if (lastAttackHero)
	{
		Buff* buff;
		if (_creepName == "tiger")
		{
			buff = Buff::create(EBuffType::NORMAL, 10.f, 0, 0, 0, 0, 0, 100, 0, 0, 0);
		}
		else if (_creepName == "lion")
		{
			buff = Buff::create(EBuffType::NORMAL, 10.f, 0, 0, 0, 0, 0, 0, 20, 0, 0);
		}
		else
		{
			buff = Buff::create(EBuffType::NORMAL, 10.f, 0, 0, 0, 0, 0, 100, 20, 0, 0);
		}
		lastAttackHero->takeBuff(buff);
		lastAttackHero->getRecordComp()->addMoney(goldForKill / 3);
		goldForKill = goldForKill * 2 / 3;
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
