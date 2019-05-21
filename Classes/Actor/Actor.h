#pragma once
#ifndef __Actor_h__
#define _Actor_h_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
#include "../Const/Constant.h"
#include "Component/Buff.h"
#include "Component/Equipment.h"
USING_NS_CC;

class StateComponent;
class Bonus;
class ExpComponent;


//enum EDamageType
//{
//	PHYSICS,
//	MAGIC
//};
//

class Actor : public cocos2d::Sprite
{
	CC_SYNTHESIZE(ECamp, _camp, Camp);
	CC_SYNTHESIZE(INT32, _defense, Defense);
	CC_SYNTHESIZE(INT32, _attack, Attack);
	CC_SYNTHESIZE(INT32, _attackRadius, AttackRadius);
	CC_SYNTHESIZE(bool, _alreadyDead, AlreadyDead);
	CC_SYNTHESIZE(INT32, _magicDefense, MagicDefense);
	CC_SYNTHESIZE(float, _lastAttackTime, LastAttackTime);
	CC_SYNTHESIZE(StateComponent*, _healthComp, HealthComp);
	CC_SYNTHESIZE(Bonus*, _bonus, Bonus);
	CC_SYNTHESIZE(Vector<Buff*>, _allBuff, AllBuff);

public:

	virtual bool die();

	virtual bool attack();

	virtual void takeBuff(Buff* buff);

	virtual void takeDamage(INT32 damge, Actor* instigator);

	virtual bool init(const std::string& filename, ECamp camp);
	//
	static Actor* create(const std::string& filename, ECamp camp);

};



#endif // !Actor_h
