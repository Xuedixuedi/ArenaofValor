#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "cocos2d.h"
#include "MovingActor.h"
#include "Component/StateComponent.h"
#include <vector>


USING_NS_CC;
using std::vector;

class SoldierPath;
class HelloWorld;

class Soldier :public MovingActor
{

	CC_SYNTHESIZE(bool, _isMovingToDest, IsMovingToDest);
	CC_SYNTHESIZE(String, _soldierType, SoldierType);
	CC_SYNTHESIZE(Actor*, _instigator, Instigator);
	CC_SYNTHESIZE(Vec2, _nextDest, NextDest);	

private:

	SoldierPath* _soldierPathPoints;

	void initData(HelloWorld* combatScene, EAttackMode attackMode, ECamp camp, ERoad road, SoldierPath* soldierPathPoints);

	void initHealthComp();

	void updateDirection();

	void startAnimation();

	virtual void die();

public:

	void attack(Actor* attackTarget);

	void moveTo(const Vec2& targetPosition);

	bool updateInstigator();

	void updateState();

	virtual bool init(HelloWorld* combatScene, EAttackMode attackMode, ECamp camp, ERoad road, SoldierPath* soldierPathPoints);

	static Soldier* create(HelloWorld* combatScene, EAttackMode attackMode, ECamp camp, ERoad road, SoldierPath* soldierPathPoints);
};


#endif // !__SOLDIER_H__
