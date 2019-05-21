#include "Buff.h"


bool Buff::init(EBuffType buffType, float duration)
{
	if (!Node::init())
	{
		return false;
	}

	_buffType = buffType;
	_duration = duration;


	return true;
}

Buff* Buff::create(EBuffType buffType, float duration)
{
	Buff* buff = new(std::nothrow)Buff;
	if (buff && buff->init(buffType, duration))
	{
		buff->autorelease();
		return buff;
	}
	CC_SAFE_DELETE(buff);
	return nullptr;
}
