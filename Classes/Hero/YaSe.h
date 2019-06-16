#ifndef __YASE_H__
#define __YASE_H__

#include "cocos2d.h"
#include "Actor/Hero.h"

USING_NS_CC;

class YaSe :public Hero
{
	CC_SYNTHESIZE(bool, _isEnhanced, IsEnhanced);
	CC_SYNTHESIZE(Sprite*, _sprSkill, SprSkill);

private:

	void updateHP(float delta);

	void applySkillDamage(float delta);

	virtual void sendBuff(float delta);

protected:

	void die() override;

public:

	virtual void castSkill_1();

	virtual void castSkill_2();

	virtual void castSkill_3();

	virtual bool attack();

	virtual bool init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

	static YaSe* create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);
};

#endif // !__HOUYI_H__
