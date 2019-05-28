#ifndef __MOVINGACTOR_H__
#define __MOVINGACTOR_H__


#include<iostream>
#include<string>
#include<time.h>
#include"cocos2d.h"
#include"Const/Constant.h"
#include"Actor.h"

USING_NS_CC;

class GameScene;

class MovingActor :public Actor
{
	CC_SYNTHESIZE(EDirection, _direction, Direction);
	CC_SYNTHESIZE(float, _standingAngle, StandingAngle);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(Animation*, _attackAnimation, AttackAnimation);

public:

	virtual bool die();

	virtual bool attack();

	virtual void takeBuff(Buff* buff);

	virtual void takeDamage(float damge, Actor* instigator);

	virtual bool init(const std::string& filename, ECamp camp,GameScene* scene);

	static MovingActor* create(const std::string& filename, ECamp camp, GameScene* scene);


};


#endif