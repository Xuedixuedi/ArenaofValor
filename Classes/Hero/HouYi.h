#pragma once
#ifndef _HouYi_h__
#define _HouYi_h_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
#include "../Const/Constant.h"
#include "Component/Buff.h"
#include "Component/Equipment.h"
#include "Actor/Hero.h"
USING_NS_CC;

class HouYi :public Hero
{
	CC_SYNTHESIZE(float, _calmTime_1, CalmTime_1);
	CC_SYNTHESIZE(float, _calmTime_2, CalmTime_2);
	CC_SYNTHESIZE(float, _calmTime_3, CalmTime_3);

	CC_SYNTHESIZE(float, _lastSkillTime_1, LastSkillTime_1);
	CC_SYNTHESIZE(float, _lastSkillTime_2, LastSkillTime_2);
	CC_SYNTHESIZE(float, _lastSkillTime_3, LastSkillTime_3);

	CC_SYNTHESIZE(INT32, _skillLevel_1, SkillLevel_1);
	CC_SYNTHESIZE(INT32, _skillLevel_2, SkillLevel_2);
	CC_SYNTHESIZE(INT32, _skillLevel_3, SkillLevel_3);

	CC_SYNTHESIZE(INT32, _punishState, PunishState);
	CC_SYNTHESIZE(float, _punishStateTime, PunishStateTime);

public:

	static HouYi * create(GameScene * scene, ECamp camp, std::string heroName, EAttackMode attackMode);
	virtual  bool init(GameScene * scene, ECamp camp, std::string heroName, EAttackMode attackMode);

	virtual void skillLevelUp(INT32 skillNumber);
	
	virtual void castSkill_1();
	virtual void castSkill_2(Point center);
	virtual void castSkill_3(Point point);

	virtual bool attack();

	virtual void updateAttackTarget();

};


#endif // !Hero
