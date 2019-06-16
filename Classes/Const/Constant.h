#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include "cocos2d.h"

#define FRAMES_PER_SECOND             30


#define ORIGIN_RADIUS				  700
#define ORIGIN_INTERVAL				  0.2
#define PRESS						  1
#define RELEASE						  2
#define MIN_ATTACK_INTERVAL			  1.0

#define VISION_RADIUS				  500

#define TOWER_MIN_ATTACK_INTERVAL	  2
#define TOWER_HP					  8000
#define TOWER_ATTACK_RADIUS           500
#define TOWER_ARMOR				      300
#define TOWER_MAGIC_DEFNESE           100
#define TOWER_ATTACK				  470

#define DEFAULT_ATTACK_RADIUS_MELEE   150
#define DEFAULT_ATTACK_RADIUS_REMOTE  400
#define DEFAULT_HOSTILITY_RADIUS	  550	

#define SOLDIER_MOVE_SPEED			  140	//240
#define SOLDIER_ARMOR				  20
#define SOLDIER_MAGIC_DEFENSE         50
#define SOLDIER_ATTACK                100 //100
#define SOLDIER_HP                    800

#define MELEE_GOLD					  30
#define MELEE_EXP					  70
#define REMOTE_GOLD					  20
#define REMOTE_EXP					  50

#define BLUE_HERO_BIRTHPLACE          Point(340, 260)
#define RED_HERO_BIRTHPLACE           Point(6060, 260)

#define MIN_DEGREE_IN_RAD             0.3926991

#define TAG_MAP						  100000
#define TAG_MYHERO					  100001

//飞行物速度
#define SPEED_FLY					  600

//TAG部分

#define TAG_MAX						  18000

#define TAG_DIE                       1752459

#define NUMBER_OF_EQUIPMENT		      9
#define	NUMBER_OF_EQUIPGRID			  6
#define EQUIP_CIRCLE_RADIUS			  40


//技能面板TAG>18000&&<19000
#define TAG_SPRSKILL_1                18001
#define TAG_SPRSKILL_2                18002
#define TAG_SPRSKILL_3                18003
#define TAG_SPRPLUS_1                 18004
#define TAG_SPRPLUS_2                 18005
#define TAG_SPRPLUS_3                 18006

//技能精灵TAG>=10000&&<18000
#define TAG_JINENG		10000
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

#define RED_TOWER_POSITION		Vec2(4464, 688)
#define BLUE_TOWER_POSITION		Vec2(1936, 688)
#define RED_SHUIJIN_POSITION	Vec2(5776, 688)
#define BLUE_SHUIJIN_POSITION   Vec2(624,688)
#define LION_BIRTHPLACE         Vec2(500, 1350)
#define PIG_BIRTHPLACE          Vec2(3200, 1350)
#define TIGER_BIRTHPLACE        Vec2(5900, 1350)

#define CHATBOX_SIZE            4


USING_NS_CC;

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

enum EEQUIPMENT
{
	CAOXIE,
	TIEJIAN,
	BISHOU,
	LANBAOSHI,
	HUFU,
	HONGBAOSHI,
	PIFENG,
	BUJIA,
	SHUIJIN,
	NOTHING
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

	Damage(INT32 damage = 0, Actor* instigator = nullptr, Actor* target = nullptr, EDamageType damageType = EDamageType::PHYSICS_DAMAGE, float actionTime = 0.f) noexcept:
		_damage(damage),
		_instiogator(instigator),
		_target(target),
		_damageType(damageType),
		_actionTime(actionTime) {}
};

struct HeroMessage
{
	int _playerNumber;
	std::string _heroName;
	ECamp camp;

	HeroMessage(int playerNumber = 0, std::string heroName = "", ECamp camp = BLUE) noexcept:
		_playerNumber(playerNumber), _heroName(heroName), camp(camp) {}
};

namespace MyMath
{
	inline float getRad(const Vec2& startPoint, const Vec2& endPoint)
	{
		float py1 = startPoint.y;
		float py2 = endPoint.y;
		//求出两边长度  
		auto delta = endPoint - startPoint;
		//开方   与  几次方 公式  
		auto distance = startPoint.distance(endPoint);
		auto cos = delta.x / distance;
		//反余弦定理，知道两边长求角度：cos = 邻边/斜边  
		auto rad = acos(cos);
		//当触屏Y坐标 <摇杆的Y坐标时，取反值  
		if (py1 > py2)
		{
			rad = 2 * M_PI - rad;
		}
		return rad;
	}

	inline Vec2 calculatePositionDelta(float angle, float speed)
	{
		return Vec2(cos(angle) * speed / FRAMES_PER_SECOND, sin(angle) * speed / FRAMES_PER_SECOND);
	}
};

#endif // !Constant_H