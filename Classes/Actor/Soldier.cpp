#include "Soldier.h"
#include "Scene/HelloWorldScene.h"
#include "PathFind/SoldierPath.h"
#include "Component/Record.h"
#include "Component/ExpComponent.h"

Soldier* Soldier::create(HelloWorld* combatScene, EAttackMode attackMode, ECamp camp, ERoad road, SoldierPath* soldierPathPoints)
{
	Soldier* soldier = new(std::nothrow)Soldier;
	if (soldier && soldier->init(combatScene, attackMode, camp, road, soldierPathPoints))
	{
		soldier->autorelease();
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}

bool Soldier::init(HelloWorld* combatScene, EAttackMode attackMode, ECamp camp, ERoad road, SoldierPath* soldierPathPoints)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	initData(combatScene, attackMode, camp, road, soldierPathPoints);
	initHealthComp();

	return true;
}

void Soldier::initData(HelloWorld* combatScene, EAttackMode attackMode, ECamp camp, ERoad road, SoldierPath* soldierPathPoints)
{
	if (attackMode == EAttackMode::MELEE)
	{
		if (camp == ECamp::BLUE)
		{
			setTexture("pictures\\soldier\\BlueMelee\\BlueMeleeRight1.png");
			_soldierType = "BlueMelee";
		}
		else
		{
			setTexture("pictures\\soldier\\RedMelee\\RedMeleeLeft1.png");
			_soldierType = "RedMelee";
		}
	}
	else
	{
		if (camp == ECamp::BLUE)
		{
			setTexture("pictures\\soldier\\BlueRemote\\BlueRemoteRight1.png");
			_soldierType = "BlueRemote";
		}
		else
		{
			setTexture("pictures\\soldier\\RedRemote\\RedRemoteLeft1.png");
			_soldierType = "RedRemote";
		}
	}

	_combatScene = combatScene;
	_soldierPathPoints = soldierPathPoints;
	_attackMode = attackMode;
	_camp = camp;
	_defense = SOLDIER_ARMOR;
	_attack = SOLDIER_ATTACK;
	_attackRadius = attackMode == EAttackMode::MELEE ? DEFAULT_ATTACK_RADIUS_MELEE : DEFAULT_ATTACK_RADIUS_REMOTE;
	_alreadyDead = false;
	_magicDefense = SOLDIER_MAGIC_DEFENSE;
	_lastAttackTime = 0;
	_moveSpeed = SOLDIER_MOVE_SPEED;
	_isMovingToDest = false;
	_instigator = nullptr;
	_minAttackInterval = MIN_ATTACK_INTERVAL;
	_isAttacking = false;
	_direction = EDirection::NODIR;
	_vertigoLastTo = 0.f;
	//_arrivedFirstDest = false;
	//_isDisturbed = false;

	if (camp == ECamp::BLUE)
	{
		if (road = ERoad::DOWNWAY)
		{
			_standingAngle = 0.f;
		}
		else if (road == ERoad::MIDWAY)
		{
			_standingAngle = 2 * MIN_DEGREE_IN_RAD;
		}
		else
		{
			_standingAngle = 4 * MIN_DEGREE_IN_RAD;
		}
	}
	else
	{
		if (road = ERoad::DOWNWAY)
		{
			_standingAngle = 12 * MIN_DEGREE_IN_RAD;
		}
		else if (road == ERoad::MIDWAY)
		{
			_standingAngle = 10 * MIN_DEGREE_IN_RAD;
		}
		else
		{
			_standingAngle = 8 * MIN_DEGREE_IN_RAD;
		}
	}
}

void Soldier::initHealthComp()
{
	_healthComp = StateComponent::create(EStateType::HEALTH, SOLDIER_HP, 0);
	auto position = getPosition();
	auto size = getBoundingBox().size;
	size.height *= 1.5;

	_healthComp->setScaleX(0.15);
	_healthComp->setScaleY(0.4);
	_healthComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_healthComp->setPosition(position + Vec2(size.width / 2, size.height * 2 / 3));
	addChild(_healthComp);
}

void Soldier::updateState()
{
	auto nowTime = GetCurrentTime() / 1000.f;
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

	if (_instigator)
	{
		if (!_instigator->getAlreadyDead())
		{
			auto distanceToInstigator = _instigator->getPosition().distance(getPosition());

			if (distanceToInstigator <= _attackRadius)
			{
				_isMovingToDest = false;
				attack(_instigator);

				return;
			}
			else if (distanceToInstigator <= VISION_RADIUS)
			{
				_isMovingToDest = false;
				moveTo(_instigator->getPosition());

				return;
			}
		}

		_instigator = nullptr;
		if (!updateInstigator())
		{
			_nextDest = _soldierPathPoints->getNextPoint(getPosition());
			_isMovingToDest = true;
			moveTo(_nextDest);
		}

		return;
	}

	_instigator = nullptr;
	if (!updateInstigator())
	{
		_isMovingToDest = true;

		if (getPosition().distance(_nextDest) < 10.f)
		{
			if (_soldierPathPoints->getNextPoint(_nextDest) == Vec2::ZERO)
			{
				stopAllActions();
				_direction = EDirection::NODIR;
				
				return;
			}
			else
			{
				_nextDest = _soldierPathPoints->getNextPoint(_nextDest);
			}
		}

		moveTo(_nextDest);

		return;
	}

	_isMovingToDest = false;
	return;
}

void Soldier::attack(Actor* attackTarget)
{
	stopAllActions();

	_isAttacking = true;
	_standingAngle = MyMath::getRad(getPosition(), attackTarget->getPosition());
	updateDirection();

	auto animation = Animation::create();

	switch (_direction)
	{
	case EDirection::DOWN:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackDown", _soldierType.getCString()));
		break;
	case EDirection::LEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackLeft", _soldierType.getCString()));
		break;
	case EDirection::RIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackRight", _soldierType.getCString()));
		break;
	case EDirection::UP:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackUp", _soldierType.getCString()));
		break;
	}

	animation->setDelayPerUnit(_minAttackInterval / 10);
	animation->setLoops(1);

	auto animate = Animate::create(animation);
	runAction(animate);

	auto nowTime = GetCurrentTime() / 1000.f;

	if (_attackMode == EAttackMode::MELEE)
	{
		auto damage = Damage(_attack, this, attackTarget, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 10 * 3);
		_combatScene->_damages.push_back(damage);
	}
	else
	{
		auto projectile = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack, SPEED_FLY, this, attackTarget);
		projectile->setScale(1.5f);
		_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 3, projectile);
	}
	_lastAttackTime = nowTime;
}

void Soldier::die()
{
	_alreadyDead = true;
	_allBuff.clear();

	auto goldForKill = _attackMode == EAttackMode::MELEE ? MELEE_GOLD : REMOTE_GOLD;
	auto expForKill = _attackMode == EAttackMode::MELEE ? MELEE_EXP : REMOTE_EXP;

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

void Soldier::moveTo(const Vec2& targetPosition)
{
	auto oldDirection = _direction;
	_standingAngle = MyMath::getRad(getPosition(), targetPosition);
	updateDirection();

	if (_direction != oldDirection)
	{
		startAnimation();
	}
	else if (_isAttacking)
	{
		_isAttacking = false;
		startAnimation();
	}

	auto newPosition = MyMath::calculatePositionDelta(_standingAngle, _moveSpeed) + getPosition();
	setPosition(newPosition);
}

void Soldier::updateDirection()
{
	if (_standingAngle <= 2 * MIN_DEGREE_IN_RAD || _standingAngle > 14 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::RIGHT;
	}
	else if (_standingAngle <= 6 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::UP;
	}
	else if (_standingAngle <= 10 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::LEFT;
	}
	else if (_standingAngle <= 14 * MIN_DEGREE_IN_RAD)
	{
		_direction = EDirection::DOWN;
	}
}

void Soldier::startAnimation()
{
	stopAllActions();

	auto animation = Animation::create();

	switch (_direction)
	{
	case EDirection::DOWN:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveDown", _soldierType.getCString()));
		break;
	case EDirection::LEFT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveLeft", _soldierType.getCString()));
		break;
	case EDirection::RIGHT:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveRight", _soldierType.getCString()));
		break;
	case EDirection::UP:
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sMoveUp", _soldierType.getCString()));
		break;
	}

	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);

	auto animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

bool Soldier::updateInstigator()
{
	auto& heroes = _combatScene->_heroes;
	for (auto& i:heroes)
	{
		if (i->getCamp() != _camp && !i->getAlreadyDead() && getPosition().distance(i->getPosition()) <= VISION_RADIUS)
		{
			_instigator = i;
			return true;
		}
	}

	auto& soldiers = _combatScene->_soldiers;
	for (auto& i : soldiers)
	{
		if (i->getCamp() != _camp && !i->getAlreadyDead() && getPosition().distance(i->getPosition()) <= VISION_RADIUS)
		{
			_instigator = i;
			return true;
		}
	}

	auto& towers = _combatScene->_towers;
	for (auto& i : towers)
	{
		if (i->getCamp() != _camp && !i->getAlreadyDead() && getPosition().distance(i->getPosition()) <= VISION_RADIUS)
		{
			_instigator = i;
			return true;
		}
	}

	return false;
}
