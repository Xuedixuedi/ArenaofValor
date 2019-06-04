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
class HelloWorld;


class Actor : public cocos2d::Sprite
{
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);
	CC_SYNTHESIZE(HelloWorld*, _combatScene, CombatScene);
	CC_SYNTHESIZE(ECamp, _camp, Camp);
	CC_SYNTHESIZE(INT32, _defense, Defense);
	CC_SYNTHESIZE(INT32, _attack, Attack);
	CC_SYNTHESIZE(INT32, _magicAttack, MagicAttack);
	CC_SYNTHESIZE(INT32, _attackRadius, AttackRadius);
	CC_SYNTHESIZE(bool, _alreadyDead, AlreadyDead);
	CC_SYNTHESIZE(INT32, _magicDefense, MagicDefense);
	CC_SYNTHESIZE(float, _lastAttackTime, LastAttackTime);
	CC_SYNTHESIZE(float, _minAttackInterval, MinAttackInterval);
	CC_SYNTHESIZE(StateComponent*, _healthComp, HealthComp);
	CC_SYNTHESIZE(Actor*, _lastAttackFrom, LastAttackFrom);
	//CC_SYNTHESIZE(Vector<Buff*>, _allBuff, AllBuff);
	CC_SYNTHESIZE(Actor*, _attackTarget, AttackTarget);

protected:

	virtual void initData(HelloWorld* combatScene, ECamp camp);

	virtual void initHealthComp();

	virtual void removeBuff(Buff* buff);

public:
	Vector<Buff*>_allBuff;

	virtual void updateAttackTarget();

	virtual void die();

	virtual bool attack();

	virtual void takeBuff(Buff* buff);

	virtual void clearBuff();

	virtual void takeDamage(EDamageType damageType, INT32 damge, Actor* instigator);

	virtual bool init(HelloWorld* combatScene, ECamp camp);
	//
	static Actor* create(HelloWorld* combatScene, ECamp camp);

};

#endif // !Actor_h
