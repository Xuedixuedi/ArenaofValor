#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define ORIGIN_RADIUS				  700
#define ORIGIN_INTERVAL				  0.2
#define PRESS						  1
#define RELEASE						  2
#define MIN_ATTACK_INTERVAL			  1.2

#define VISION_RADIUS				  600

#define TOWER_MIN_ATTACK_INTERVAL	  2
#define TOWER_HP					  5000
#define TOWER_ATTACK_RADIUS           500
#define TOWER_ARMOR				      100
#define TOWER_MAGIC_DEFNESE           100
#define TOWER_ATTACK				  500

#define DEFAULT_ATTACK_RADIUS_MELEE   100
#define DEFAULT_ATTACK_RADIUS_REMOTE  400
#define DEFAULT_HOSTILITY_RADIUS	  500	

#define SOLDIER_MOVE_SPEED			  400
#define SOLDIER_ARMOR				  50
#define SOLDIER_MAGIC_DEFENSE         50
#define SOLDIER_ATTACK                100
#define MIN_DEGREE_IN_RAD             0.3926991
#define SOLDIER_HP                    1000

#define TAG_MAP						  100000
#define TAG_MYHERO					  100001

//飞行物速度
#define SPEED_FLY                     600

//TAG部分

#define TAG_MAX                       18000

//技能精灵TAG>=10000&&<18000
#define TAG_JINENG      10000
#define TAG_DAJI_SKILL1 14010
#define TAG_DAJI_SKILL2 14020
#define TAG_DAJI_SKILL3 14030

#define TAG_HOUYI_SKILL1 15010
#define TAG_HOUYI_SKILL2 15020
#define TAG_HOUYI_SKILL3 15030

#define TAG_YASE_SKILL1 16010
#define TAG_YASE_SKILL2 16020
#define TAG_YASE_SKILL3 16030

//英雄TAG>=5000&&<10000
#define TAG_HERO 5000
#define TAG_HOUYI 5001
#define TAG_YASE 6000
#define TAG_DAJI 7000

//移动物TAG>=2000&&<5000
#define TAG_MOVINGACTOR 2000
#define TAG_JIN 2001
#define TAG_ZHONG 2010
#define TAG_YUAN 2020
#define TAG_CHE 2030

//静止物TAG>=1000&&<2000
#define TAG_ACTOR 1000
#define TAG__TA 1001
#define TAG_JIA 1010

class Actor;

enum ECamp 
{
	BLUE, 
	RED, 
	MID
};

enum EAttackMode
{
	MELEE,
	REMOTE
};

enum ERoad
{
	TOPWAY,
	MIDWAY,
	DOWNWAY
};

enum EDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UPLEFT,
	UPRIGHT,
	DOWNLEFT,
	DOWNRIGHT,
	NODIR
};

enum EDamageType
{
	PHYSICS_DAMAGE,
	MAGIC_DAMAGE
};

typedef std::vector<std::vector<bool>> DyaDicVector;

typedef struct PointINT
{
	INT32 x, y;

	PointINT(INT32 x = 0, INT32 y = 0) :x(x), y(y) {}

	PointINT& operator = (const cocos2d::Vec2& point)
	{
		x = static_cast<INT32>(point.x);
		y = static_cast<INT32>(point.y);
		return *this;
	}


}SizeINT;



struct Damage
{
	INT32 _damage;
	Actor* _instiogator;
	Actor* _target;
	EDamageType _damageType;
	float _actionTime;

	Damage(INT32 damage = 0, Actor* instigator = nullptr, Actor* target = nullptr, EDamageType damageType = EDamageType::PHYSICS_DAMAGE, float actionTime = 0.f) :
		_damage(damage),
		_instiogator(instigator),
		_target(target),
		_damageType(damageType),
		_actionTime(actionTime) {}
};
#endif // !Constant_H
