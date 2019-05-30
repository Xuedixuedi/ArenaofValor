#ifndef __BUFF_H__
#define __BUFF_H__

#include "cocos2d.h"

USING_NS_CC;

enum EBuffType
{
	VERTIGO,	//—£‘Œ
	SILENCE,	//≥¡ƒ¨
	MULTIPLE,	//∑÷¡—π•ª˜
	NORMAL
};

class Buff : public cocos2d::Node
{
public:
	// Ù–‘
	CC_SYNTHESIZE(INT32, _attack, Attack);
	CC_SYNTHESIZE(INT32, _defense, Defense);
	CC_SYNTHESIZE(INT32, _magicDefense, MagicDefense);
	CC_SYNTHESIZE(INT32, _HP, HP);
	CC_SYNTHESIZE(INT32, _MP, MP);
	CC_SYNTHESIZE(INT32, _HPRecover, HPRecover);
	CC_SYNTHESIZE(INT32, _MPRecover, MPRevoer);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(float, _attackInterval, AttackInterval);

	CC_SYNTHESIZE(EBuffType, _buffType, BuffType);

	CC_SYNTHESIZE(float, _duration, Duration);
	CC_SYNTHESIZE(float, _beginTime, BeginTime);
	CC_SYNTHESIZE(float, _endTime, EndTime);

	virtual bool init(EBuffType buffType, float duration, INT32 attack,
		INT32 defense, INT32 magicDefense, INT32 HP, INT32 MP,
		INT32 HPRecover, INT32 MPRecover, float moveSpeed, float attackInterval
	);

	static Buff* create(EBuffType buffType, float duration, INT32 attack,
		INT32 defense, INT32 magicDefense, INT32 HP, INT32 MP,
		INT32 HPRecover, INT32 MPRecover, float moveSpeed, float attackInterval
	);
};

#endif // !__BUFF_H__

