#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define ORIGIN_RADIUS				  700
#define ORIGIN_INTERVAL				  0.2
#define PRESS						  1
#define RELEASE						  2
#define MIN_ATTACK_INTERVAL			  0.2
#define VISION_RADIUS				  500
#define DEFAULT_ATTACK_RADIUS_MELEE   100
#define DEFAULT_ATTACK_RADIUS_REMOTE  400
#define TOWER_ATTACK_RADIUS           500
#define MIN_DEGREE_IN_RAD             0.3926991


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

#endif // !Constant_H
