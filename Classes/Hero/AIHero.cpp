#include "AIHero.h"
#include "Scene/HelloWorldScene.h"
#include "PathFind/SoldierPath.h"

AIHero* AIHero::create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode, SoldierPath* pathPoints)
{
	AIHero* aiHero = new(std::nothrow)AIHero;
	if (aiHero && aiHero->init(combatScene, camp, heroName, attackMode, pathPoints))
	{
		aiHero->autorelease();
		return aiHero;
	}
	CC_SAFE_DELETE(aiHero);
	return nullptr;
}

bool AIHero::init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode, SoldierPath* pathPoints)
{
	if (!Hero::init(combatScene, camp, heroName, attackMode))
	{
		return false;
	}

	_isMovingToDest = false;
	_instigator = nullptr;
	_pathPoints = pathPoints;

	return true;
}

void AIHero::updateState()
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

	if (_instigator)
	{
		if (!_instigator->getAlreadyDead())
		{
			auto distanceToInstigator = _instigator->getPosition().distance(getPosition());

			if (distanceToInstigator <= _attackRadius)
			{
				_isMovingToDest = false;
				attack();

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
			_nextDest = _pathPoints->getNextPoint(getPosition());
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
			if (_pathPoints->getNextPoint(_nextDest) == Vec2::ZERO)
			{
				stopAllActions();
				_direction = EDirection::NODIR;

				return;
			}
			else
			{
				_nextDest = _pathPoints->getNextPoint(_nextDest);
			}
		}

		moveTo(_nextDest);

		return;
	}

	_isMovingToDest = false;
	return;
}

bool AIHero::updateInstigator()
{
	auto& heroes = _combatScene->_heroes;
	for (auto& i : heroes)
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

void AIHero::moveTo(const Vec2& targetPosition)
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

void AIHero::startAnimation()
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

	animation->setDelayPerUnit(_minAttackInterval / 5);
	animation->setLoops(-1);

	auto animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

bool AIHero::attack()
{
	updateAttackTarget();
	if (!_attackTarget)
	{
		return false;
	}
	stopAllActions();
	_isAttacking = true;
	_standingAngle = MyMath::getRad(getPosition(), _attackTarget->getPosition());
	updateDirection();

	playAttackAnimation();

	auto nowTime = GetCurrentTime() / 1000.f;

	if (_attackMode == EAttackMode::MELEE)
	{
		auto damage = Damage(_attack, this, _attackTarget, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 10 * 3);
		_combatScene->_damages.push_back(damage);
	}
	else
	{
		auto projectile = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack, SPEED_FLY, this, _attackTarget);
<<<<<<< HEAD
		if (std::string(_heroName.getCString()) == "DaJi")
		{
			projectile->setTexture("pictures/hero/DaJi/Normal.png");
		}
=======

>>>>>>> be5a403484c859dd963eeabb6a4cd558b1dd24ac
		projectile->setScale(1.5f);
		if (std::string(_heroName.getCString()) == "DaJi")
		{
			projectile->setTexture("pictures/hero/DaJi/Normal.png");
			projectile->setScale(0.2);
		}
		_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 3, projectile);
	}
	_lastAttackTime = nowTime;
}
