#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Actor/Projectile.h"
#include "Actor/Actor.h"

USING_NS_CC;

class Record;
class Hero;
class HRocker;

class HelloWorld : public cocos2d::Scene
{
	CC_SYNTHESIZE(Vector<Projectile*>, _bullets, Bullets);
	CC_SYNTHESIZE(Vector<Actor*>, _actors, AllActor);
	CC_SYNTHESIZE(Record*, _labelRecord, LabelRecord);
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(Size, _visibleSize, VisibleSize);
	CC_SYNTHESIZE(Vec2, _origin, Origin);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);

private:

	void initLabelRecord();

	void initHero();

	void initHRocker();

	void updateHeroPosition();

public:

    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void loadingAnimation();
	
	virtual void update(float delta);

	void launch(float delta);

	void test();

    CREATE_FUNC(HelloWorld);

};

#endif 
