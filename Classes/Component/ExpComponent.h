#ifndef __EXPCOMPONENT_H__
#define __EXPXOMPONENT_H__

#include "cocos2d.h"

USING_NS_CC;

class ExpComponent :public cocos2d::Sprite
{
	CC_SYNTHESIZE(INT32, _level, Level);
	CC_SYNTHESIZE(INT32, _currentExp, CurrentEXP);
	CC_SYNTHESIZE(INT32, _levelUpNeededExp, LevelUpNeededExp);

private:

	Label* _labelLevel;

public:

	void addExp(INT32 Exp);

	bool init(INT32 levelUpNeededExp);

	static ExpComponent* create(INT32 levelUpNeededExp);
};

#endif // !__EXPCOMPONENT_H__
