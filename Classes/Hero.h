#pragma once
#ifndef _Hero_h_

#define _Hero_h_

#include<iostream>
#include<string>
#include<time.h>
#include "cocos2d.h"
#include"Constant.h"
#include "MovingActor.h"
USING_NS_CC;

class Buff;
class Health;
class Equip;
class SkillPanel;
class Record;
class Hero :public MovingActor
{

	CC_SYNTHESIZE(Health*, _level, Level);
	CC_SYNTHESIZE(Health*, _blue, Blue);
	CC_SYNTHESIZE(int, _money, Money);
	CC_SYNTHESIZE(int, _resurgence, Resurgence);
	CC_SYNTHESIZE(Record*, _record, Record);
	CC_SYNTHESIZE(Vector<Equip*>, _inventory, Inventory);
	CC_SYNTHESIZE(Vector<SkillPanel*>, _skillPanel, SkillPanel);
public:
	virtual bool skill0();
	virtual bool skill1();
	virtual bool skill2();
	virtual bool skill3();
};
#endif