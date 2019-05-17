#ifndef __BUFF_H__
#define __BUFF_H__

#include "cocos2d.h"

USING_NS_CC;

enum EBuffType
{
	VERTIGO,	//—£‘Œ
	SILENCE,	//≥¡ƒ¨
	SLOWDOWN,	//ºıÀŸ
	REDBUFF,	//∫ÏBUFF
	BLUEBUFF	//¿∂BUFF
};

class Buff
{
public:

	Buff(EBuffType buffType, float duration);

	CC_SYNTHESIZE(EBuffType, _buffType, BuffType);
	CC_SYNTHESIZE(float, _duration, Duration);
};

#endif // !__BUFF_H__
