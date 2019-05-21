#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "cocos2d.h"
#include "MovingActor.h"

USING_NS_CC;

class Soldier :public MovingActor
{
	CC_SYNTHESIZE(Vec2, _firstDest, FirstDest);
	CC_SYNTHESIZE(Vec2, _secondDest, SecondDest);
	CC_SYNTHESIZE(bool, _arrivedFirstDest, ArrivedFirstDest);
	CC_SYNTHESIZE(bool, _isDisturbed, IsDisturbed);
	CC_SYNTHESIZE(Actor*, _instigator, Instigator);

public:

	void moveToNextDest();

	virtual bool init(ECamp camp, ERoad road);

	Static Soldier* create(ECamp camp, ERoad road);
};


#endif // !__SOLDIER_H__
