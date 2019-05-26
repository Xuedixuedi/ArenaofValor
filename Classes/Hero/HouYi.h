#ifndef __HOUYI_H__
#define __HOUYI_H__

#include "cocos2d.h"
#include "Actor/Hero.h"

USING_NS_CC;

class HelloWorld;

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
	CC_SYNTHESIZE(INT32, _punishStateTime, PunishStateTime);

public:
	
	virtual void skillLevelUp(INT32 skillNumber);

	virtual void castSkill_1();

	virtual void castSkill_2(Point mousePosition);

	virtual void castSkill_3();

	virtual bool attack();

	virtual bool init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

	static HouYi* create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);
};

#endif // !__HOUYI_H__
