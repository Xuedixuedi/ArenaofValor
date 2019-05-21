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

class Buff: public cocos2d::Node
{
public:

	CC_SYNTHESIZE(EBuffType, _buffType, BuffType);
	CC_SYNTHESIZE(float, _duration, Duration);
	CC_SYNTHESIZE(float, _beginTime, BeginTime);
	CC_SYNTHESIZE(float, _endTime, EndTime);

	virtual bool init(EBuffType buffType, float duration);

	static Buff* create(EBuffType buffType, float duration);
};

#endif // !__BUFF_H__
