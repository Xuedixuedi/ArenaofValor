#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "MovingActor.h"
#include "Actor.h"

class ExpComponent;
class StateComponent;
class Record;

USING_NS_CC;

class Hero :public MovingActor
{
	CC_SYNTHESIZE(EAttackMode, _attackMode, AttackMode);
	CC_SYNTHESIZE(float, _lastTimeDead, LastTimeDead);
	CC_SYNTHESIZE(float, _lastTimeReborn, LastTimeReborn);
	CC_SYNTHESIZE(float, _resurgenceTime, ResurgenceTime);
	CC_SYNTHESIZE(String, _heroName, HeroName);
	CC_SYNTHESIZE(ExpComponent*, _expComp, ExpComp);
	CC_SYNTHESIZE(StateComponent*, _magicComp, MagicComp);
	CC_SYNTHESIZE(Record*, _recordComp, RecordComp);
	CC_SYNTHESIZE(float, _silenceLastTo, SilenceLastTo);
	CC_SYNTHESIZE(float, _multipleLastTo, MultipleLastTo);

	CC_SYNTHESIZE(float, _calmTime_1, CalmTime_1);
	CC_SYNTHESIZE(float, _calmTime_2, CalmTime_2);
	CC_SYNTHESIZE(float, _calmTime_3, CalmTime_3);

	CC_SYNTHESIZE(float, _lastSkillTime_1, LastSkillTime_1);
	CC_SYNTHESIZE(float, _lastSkillTime_2, LastSkillTime_2);
	CC_SYNTHESIZE(float, _lastSkillTime_3, LastSkillTime_3);

	CC_SYNTHESIZE(float, _magicConsume_1, MagicConsume_1);
	CC_SYNTHESIZE(float, _magicConsume_2, MagicConsume_2);
	CC_SYNTHESIZE(float, _magicConsume_3, MagicConsume_3);

	CC_SYNTHESIZE(INT32, _skillLevel_1, SkillLevel_1);
	CC_SYNTHESIZE(INT32, _skillLevel_2, SkillLevel_2);
	CC_SYNTHESIZE(INT32, _skillLevel_3, SkillLevel_3);

	CC_SYNTHESIZE(INT32, _skillPoint, SkillPoint);

public:

	virtual bool checkSkillStatus(INT32 skillNumber);

	virtual bool attack();

	virtual void takeDamage(EDamageType damageType, INT32 damage, Actor* instigator);

	virtual void takeBuff(Buff* buff);

	virtual void skillLevelUp(INT32 skillNumber);

	virtual void castSkill_1();

	virtual void castSkill_1(Point mousePosition);

	virtual void castSkill_2();

	virtual void castSkill_2(Point mousePosition);

	virtual void castSkill_3();

	virtual void castSkill_3(Point mousePosition);

	virtual void reborn();

	virtual void heroMove();

	virtual void stopMove();

	virtual void addExp(INT32 delta);

	virtual bool init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

	static Hero* create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

protected:
	virtual void playAttackAnimation();

	virtual void updateAttackTarget(INT32 radius);

	virtual void updateAttackTarget();

	ValueMap _heroDataAtEachLevel;

	ValueMap _heroData;

	ValueMap _commonData;

	Map<float, Hero*> _causeDamageActors;

	ValueMap _skillData;

	virtual void levelUp();

	virtual void die();

	virtual void removeAllBuff();

	virtual void removeBuff(Buff* buff);

	virtual void updateDirection();

	virtual void startAnimation();

	virtual bool initHeroData(HelloWorld* combatScene, std::string heroName, ECamp camp, EAttackMode attackMode);

	virtual bool initHealthComp(std::string heroName);

	virtual bool initMagicComp(std::string heroName);

	virtual bool initExpComp();

	virtual bool initRecordComp();
};

#endif // !__HERO_H__
