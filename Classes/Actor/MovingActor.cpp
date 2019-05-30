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
	}
}