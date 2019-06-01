#ifndef __MOVINGACTOR_H__
#define __MOVINGACTOR_H__


#include<iostream>
#include<string>
#include<time.h>
#include"cocos2d.h"
#include"Actor.h"

USING_NS_CC;


class MovingActor :public Actor
{
	CC_SYNTHESIZE(EAttackMode, _attackMode, AttackMode);
	CC_SYNTHESIZE(EDirection, _direction, Direction);
	CC_SYNTHESIZE(float, _standingAngle, StandingAngle);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(Animation*, _attackAnimation, AttackAnimation);
	CC_SYNTHESIZE(float, _vertigoLastTo, VertigoLastTo);

protected:

	virtual void die();

	virtual void removeBuff(Buff* buff);

public:

	virtual bool attack();

	virtual void takeBuff(Buff* buff);



	virtual bool init(const std::string& filename, ECamp camp);

	static MovingActor* create(const std::string& filename, ECamp camp);

};


#endif