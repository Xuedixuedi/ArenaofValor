#include "Buff.h"

Buff* Buff::create(EBuffType buffType, float duration, INT32 attack,
	INT32 defense, INT32 magicDefense, INT32 HP, INT32 MP,
	INT32 HPRecover, INT32 MPRecover, float moveSpeed, float attackInterval)
{
	Buff* buff = new(std::nothrow)Buff;
	if (buff && buff->init(buffType, duration, attack, defense, magicDefense, HP,
		MP, HPRecover, MPRecover, moveSpeed, attackInterval
	))
	{
		buff->autorelease();

		return buff;
	}
	CC_SAFE_DELETE(buff);
	return nullptr;
}

bool Buff::init(EBuffType buffType, float duration, INT32 attack,
	INT32 defense, INT32 magicDefense, INT32 HP, INT32 MP,
	INT32 HPRecover, INT32 MPRecover, float moveSpeed, float attackInterval)
{
	if (!Sprite::init())
	{
		return false;
	}
	//≥ı ºªØ Ù–‘
	_attack = attack;
	_defense = defense;
	_magicDefense = magicDefense;
	_HP = HP;
	_MP = MP;
	_HPRecover = HPRecover;
	_MPRecover = MPRecover;
	_moveSpeed = moveSpeed;
	_attackInterval = attackInterval;

	//
	_buffType = buffType;
	_duration = duration;
	_beginTime = GetCurrentTime() / 1000.f;
	_endTime = _beginTime + duration;
	return true;
}

bool Buff::init(ValueVector& data)
{
	if (!Sprite::init())
	{
		return false;
	}

	_buffType = EBuffType::NORMAL;
	_duration = data.at(0).asFloat();
	_attack = data.at(1).asInt();
	_defense = data.at(2).asInt();
	_magicDefense = data.at(3).asInt();
	_HP = data.at(4).asInt();
	_MP = data.at(5).asInt();
	_HPRecover = data.at(6).asInt();
	_MPRecover = data.at(7).asInt();
	_moveSpeed = data.at(8).asFloat();
	_attackInterval = data.at(9).asFloat();

	return true;
}
