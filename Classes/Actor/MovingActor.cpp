#include "Actor.h"
#include "Component/StateComponent.h"
#include "MovingActor.h"


MovingActor* MovingActor::create(const std::string& filename, ECamp camp)
{
	MovingActor* sprite = new (std::nothrow)MovingActor();
	if (sprite && sprite->init(filename, camp))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool MovingActor::init(const std::string& filename, ECamp thisCamp)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	return true;
}


void MovingActor::die()
{
}

void MovingActor::removeBuff(Buff* buff)
{
	Actor::removeBuff(buff);

	_moveSpeed -= buff->getMoveSpeed();
}

void MovingActor::updateDirection()
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

void MovingActor::startAnimation()
{
}

void MovingActor::moveTo(const Vec2& targetPosition)
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

bool MovingActor::attack()
{
	return false;
}

void MovingActor::takeBuff(Buff* buff)
{
	Actor::takeBuff(buff);

	_moveSpeed += buff->getMoveSpeed();
	if (buff->getBuffType() == EBuffType::VERTIGO)
	{
		_vertigoLastTo = std::max(_vertigoLastTo, buff->getEndTime());
		log("%f", _vertigoLastTo);
	}
}