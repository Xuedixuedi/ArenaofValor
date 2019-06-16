#ifndef __CREEP_H__
#define __CREEP_H__

#include "cocos2d.h"
#include "MovingActor.h"

USING_NS_CC;

class Creep :public MovingActor
{
	CC_SYNTHESIZE(std::string, _creepName, CreepName);
	CC_SYNTHESIZE(Vec2, _birthPlace, BirthPlace);
	CC_SYNTHESIZE(bool, _isMovingBack, IsMovingBack);
	CC_SYNTHESIZE(Actor*, _instigator, Instigator);

private:

	void initData(HelloWorld* combatScene, const std::string& creepName);
	void initHealthComp();
	void attack(Actor* attackTarget);
	virtual void die();
	virtual void startAnimation();

public:

	virtual void updateState();
	virtual void takeDamage(EDamageType damageType, INT32 damage, Actor* instigator);

	virtual bool init(HelloWorld* combatScene, const std::string& creepName);

	static Creep* create(HelloWorld* combatScene, const std::string& creepName);
};

#endif // !__CREEP_H__
