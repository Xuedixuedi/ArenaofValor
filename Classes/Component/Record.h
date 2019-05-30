#ifndef __RECORD_H__
#define __RECORD_H__

#include "cocos2d.h"

USING_NS_CC;

class Record :public cocos2d::Layer
{
	CC_SYNTHESIZE(INT32, _kill, Kill);
	CC_SYNTHESIZE(INT32, _death, Death);
	CC_SYNTHESIZE(INT32, _assist, Assist);
	CC_SYNTHESIZE(INT32, _money, Money);

private:

	Label* _labelKill;
	Label* _labelDeath;
	Label* _labelAssist;
	Label* _labelMoney;

public:

	bool init();

	void initSprite();

	void initLabel();

	void updateKill();

	void updateAssist();

	void updateDeath();

	void updateMoney(float delta);

	void addMoney(INT32 delta);

	CREATE_FUNC(Record);
};

#endif // !__RECORD_H__
