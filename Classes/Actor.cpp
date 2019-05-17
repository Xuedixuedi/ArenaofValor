#include "Actor.h"
#include "HealthComponent.h"
#include "Constant.h"
#include "Constant.h"


Actor* Actor::create(const std::string& filename,ECamp camp)
{
	Actor *sprite = new (std::nothrow)Actor();
	if (sprite&&sprite->init(filename, camp))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Actor::init(const std::string& filename,ECamp thisCamp)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	_health = HealthComponent::create(2000.0, 1.0);
	this->addChild(_health);
	_health->setPosition(Vec2(140, 400));
	
	setAlreadyDead(false);
	setDefense(ORIGIN_DEFENSE);
	setAttack(ORIGIN_ATTACK);
	setAttackRadius(ORIGIN_RADIUS);
	setCamp(thisCamp);
	//TODO : BONUS
	setAttack(ORIGIN_INTERVAL);
	//TODO : PlayerName
	return true;
}
bool Actor::attack()
{
	return false;
}

bool Actor::die()
{
	return false;
}
