#ifndef __BONUS_H__
#define __BONUS_H__

#include "cocos2d.h"

USING_NS_CC;

class Buff;

class Bonus
{
public:

	Bonus(float exp, int gold, Buff* buff);

	~Bonus();

	CC_SYNTHESIZE(float, _exp, EXP);
	CC_SYNTHESIZE(int, _gold, Gold);
	CC_SYNTHESIZE(Buff*, _buff, Buff);

	void increaseExp(float delta);

	void increaseGold(int delta);

};

#endif // !__BONUS_H__
