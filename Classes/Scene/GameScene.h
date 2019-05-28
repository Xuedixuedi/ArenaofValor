#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Actor/Projectile.h"
#include "Actor/Actor.h"
#include "Actor/Soldier.h"
#include "Actor/Hero.h"
#include <vector>

USING_NS_CC;

class Record;
class Hero;
class HRocker;

class GameScene : public cocos2d::Scene
{
	CC_SYNTHESIZE(Vector<Projectile*>, _bullets, Bullets);
	
	CC_SYNTHESIZE(Vector<Soldier*>, _soldiers, AllSoldiers);	
	CC_SYNTHESIZE(Vector<Hero*>, _heros, AllHeros);
	CC_SYNTHESIZE(Vector<Actor*>, _towers, AllTowers);
	CC_SYNTHESIZE(std::vector<Damage>, _damages, AllDamages);

	CC_SYNTHESIZE(Record*, _labelRecord, LabelRecord);
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(Size, _visibleSize, VisibleSize);
	CC_SYNTHESIZE(Vec2, _origin, Origin);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	CC_SYNTHESIZE(TMXTiledMap*, _map, Map);

private:
	//初始化
	void generateSoldiers(float delta);
	void initMapLayer();
	void initLabelRecord();
	void initHero();
	void initHRocker();
	//更新英雄位置
	void updateHeroPosition();
	//更新攻击目标
	void updateTowerAttackTarget();
	void updateSoldiersAttackTarget();

	//监听器
	EventListenerTouchOneByOne* listenerTouch;
	EventListenerKeyboard* listenerKeyBoard;
	//鼠标点击事件
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual bool onTouchMoved(Touch* touch, Event* event);
	virtual bool onTouchEnded(Touch* touch, Event* event);

	//按键事件
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event);
	//判断是否一直被按住
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void loadingAnimation();
	virtual void update(float delta);
	void updateAttackTarget();
		
	void CircleDamage(Point point,float radius, float damage);
	
	void test();
	void launch(float delta);
    CREATE_FUNC(GameScene);
};

#endif 
