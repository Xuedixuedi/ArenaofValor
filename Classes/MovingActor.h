#pragma once
#ifndef _MovingActor_h_

#define _MovingActor_h_

#include<iostream>
#include<string>
#include<time.h>
#include "cocos2d.h"
#include"Constant.h"
#include "Actor.h"
USING_NS_CC;

class Buff;

class MovingActor :public Actor
{
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(Animation*, _attackAnimation, AttackAnimation);
	CC_SYNTHESIZE(Vector<Buff*>, _buff, Buff);
	CC_SYNTHESIZE(float, _magicDefense, MagicDefense);
public:

};


#endif