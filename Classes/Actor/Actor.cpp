#include "Actor.h"
#include "../Component/Bonus.h"
#include "../Component/StateComponent.h"
#include "Component/ExpComponent.h"

Actor* Actor::create(const std::string& filename, ECamp camp, GameScene* scene)
{
	Actor* sprite = new (std::nothrow) Actor();
	if (sprite && sprite->init(filename, camp, scene))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Actor::init(const std::string& filename, ECamp thisCamp, GameScene* scene)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	_combatScene = scene;
	//auto size = getBoundingBox().size;

	//_health = StateComponent::create(EStateType::HEALTH, 2000, 1);
	//this->addChild(_health);
	//_health->setPosition(getPosition()+Vec2(size.width/2,size.height));
	//_health->setScaleY(1.4);

	//setAlreadyDead(false);
	//setDefense(ORIGIN_DEFENSE);
	//setAttack(ORIGIN_ATTACK);
	//setAttackRadius(ORIGIN_RADIUS);
	//setCamp(thisCamp);
	////TODO : BONUS
	//setAttack(ORIGIN_INTERVAL);
	////TODO : PlayerName
	return true;
}

void Actor::takeBuff(Buff* buff)
{
	_allBuff.pushBack(buff);
//	if(buff)
}

void Actor::takeDamage(INT32 damage, Actor* instigator)
{
	_lastAttackFrom = instigator;

	if (_healthComp->getCurrentState() < damage)
	{
		_alreadyDead = true;
	}
	_healthComp->changeStateBy(-1 * damage);
}

bool Actor::attack()
{
	_lastAttackTime = GetCurrentTime();

	return false;
}



bool Actor::die()
{
	return false;
}