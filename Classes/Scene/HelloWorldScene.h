#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Actor/Projectile.h"
#include "Actor/Soldier.h"
#include "Actor/Hero.h"
#include "Actor/Actor.h"
#include "Const/Constant.h"
#include "Const/MapInfo.h"

USING_NS_CC;

class Record;
class HRocker;
class SoldierPath;

class HelloWorld : public cocos2d::Scene
{
	//CC_SYNTHESIZE(Vector<Actor*>, _allTowers, AllTowers);
	//CC_SYNTHESIZE(Vector<Projectile*>, _bullets, Bullets);
	//CC_SYNTHESIZE(Vector<Hero*>, _allHeroes, AllHeroes);
	//CC_SYNTHESIZE(std::vector<Damage>, _allDamages, AllDamages);
	//CC_SYNTHESIZE(Vector<Soldier*>, _allSoldiers, AllSoldiers);
	CC_SYNTHESIZE(Record*, _labelRecord, LabelRecord);
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(Size, _visibleSize, VisibleSize);
	CC_SYNTHESIZE(Vec2, _origin, Origin);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	CC_SYNTHESIZE(TMXTiledMap*, _map, Map);
	CC_SYNTHESIZE(MapInfo, _mapInformation, MapInformation);

public:

	Vector<Ref*> _actors;

	Vector<Actor*> _towers;

	Vector<Projectile*> _bullets;

	Vector<Hero*> _heroes;

	Vector<Soldier*> _soldiers;

	std::vector<Damage> _damages;

private:

	SoldierPath* _soldierPathPoints;

	void generateSoldiers(float delta);

	void initMapLayer();

	void initLabelRecord();

	void initHero();

	void initHRocker();

	void updateHeroPosition();

	void initTower();

	void clearObjects();

	void TowerAttack();

	void updateBullets();

	void updateDamages();

	void updateSoldiersState();

public:

    static cocos2d::Scene* createScene();

	virtual void loadingAnimation();
	
	virtual void update(float delta);

    virtual bool init();

    CREATE_FUNC(HelloWorld);

};

#endif 
