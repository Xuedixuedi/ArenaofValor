#ifndef __DAJI_H__
#define __DAJI_H__

#include "cocos2d.h"
#include "Actor/Hero.h"

USING_NS_CC;

class HelloWorld;

class DaJi :public Hero
{
	CC_SYNTHESIZE(float, _shockWaveAngle, ShockWaveAngle);
	CC_SYNTHESIZE(Vec2, _skillPosition, SkillPosition);
	//TODO;被动->降低魔抗的被动
public:

	virtual void castSkill_1(Point mousePosition);

	virtual void castSkill_2();

	virtual void castSkill_3();

	virtual void updateSprSkill_1_Position(float delta);

	virtual bool attack();

	virtual bool init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

	static DaJi* create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

};

#endif