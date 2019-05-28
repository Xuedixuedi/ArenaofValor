#include "Actor.h"
#include "Component/StateComponent.h"
#include "Const/Constant.h"
#include "MovingActor.h"


MovingActor* MovingActor::create(const std::string& filename, ECamp camp, GameScene* scene)
{
	MovingActor* sprite = new (std::nothrow)MovingActor();
	if (sprite && sprite->init(filename, camp, scene))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool MovingActor::init(const std::string& filename, ECamp thisCamp, GameScene* scene)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	_combatScene = scene;
	//_health = StateComponent::create(EStateType::HEALTH, 2000, 5);
	//this->addChild(_health);
	//_health->setPosition(Vec2(140, 400));
	//_moveSpeed = 10;
	//_magicDefense = 100;

	////还有很多没init，自己去看.h

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


bool MovingActor::die()
{
	return false;
}


bool MovingActor::attack()
{
	return false;
}

void MovingActor::takeBuff(Buff* buff)
{
	this->getAllBuff().pushBack(buff);
	_attack += buff->getAttack();
	_defense += buff->getDefense();
	_magicDefense += buff->getMagicDefense();
	_healthComp->changeMaxBy(buff->getHP());
	_healthComp->changeRecoverRate(buff->getHPRecover());
	_moveSpeed += buff->getMoveSpeed();
	_minAttackInterval -= buff->getAttackInterval();
	

}

void MovingActor::takeDamage(float damge, Actor* instigator)
{
}

