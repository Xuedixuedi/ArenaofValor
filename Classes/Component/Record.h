#ifndef __RECORD_H__
#define __RECORD_H__

#include "cocos2d.h"

USING_NS_CC;

class Record :public cocos2d::Layer
{
	//1  «Œ“∑Ω”¢–€
	CC_SYNTHESIZE(INT32, _kill1, Kill1);
	CC_SYNTHESIZE(INT32, _death1, Death1);
	CC_SYNTHESIZE(INT32, _assist1, Assist1);

	//2 ai”¢–€
	CC_SYNTHESIZE(INT32, _kill2, Kill2);
	CC_SYNTHESIZE(INT32, _death2, Death2);
	CC_SYNTHESIZE(INT32, _assist2, Assist2);

	CC_SYNTHESIZE(INT32, _money, Money);

	CC_SYNTHESIZE(Sprite*, _sprKill, SprKill);
	CC_SYNTHESIZE(Sprite*, _sprAssist, SprAssist);
	CC_SYNTHESIZE(Sprite*, _sprDeath, SprDeath);
	CC_SYNTHESIZE(Sprite*, _sprGold, SprGold);
	CC_SYNTHESIZE(Sprite*, _sprKDA, SprKDA);

private:

	//1 Œ“∑Ω”¢–€
	Label* _labelKill1;
	Label* _labelDeath1;
	Label* _labelAssist1;

	//2 ai”¢–€
	Label* _labelKill2;
	Label* _labelDeath2;
	Label* _labelAssist2;

	Label* _labelMoney;
	//Label* _

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
