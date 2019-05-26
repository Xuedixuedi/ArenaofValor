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
	CC_SYNTHESIZE(String, _heroName, HeroName);
	CC_SYNTHESIZE(ExpComponent*, _expComp, ExpComp);
	CC_SYNTHESIZE(StateComponent*, _magicComp, MagicComp);
	CC_SYNTHESIZE(Vector<Actor*>, _causeDamageActors, CauseDamageActors);
	CC_SYNTHESIZE(Record*, _recordComp, RecordComp);

public:


	virtual bool die();

	virtual bool attack();

	virtual void takeBuff(Buff* buff);

	virtual void skillLevelUp(INT32 skillNumber);

	virtual void castSkill_1();

	virtual void castSkill_2(Point mousePosition);

	virtual void castSkill_3();

	virtual void reborn();

	virtual void takeDamage(EDamageType damageType, float damge, Actor* instigator);

	virtual bool levelUp();

	virtual void heroMove();

	virtual void stopMove();

	virtual bool init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

	static Hero* create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode);

protected:

	virtual void updateDirection();

	virtual void startAnimation();

	virtual bool initHeroData(HelloWorld* combatScene, std::string heroName, ECamp camp, EAttackMode attackMode);

	virtual bool initHealthComp(std::string heroName);

	virtual bool initMagicComp(std::string heroName);

	virtual bool initExpComp();

	virtual bool initRecordComp();
};

#endif // !__HERO_H__
