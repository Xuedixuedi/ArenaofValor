#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Actor/Projectile.h"
#include "Actor/Soldier.h"
#include "Actor/Hero.h"
#include "Actor/Actor.h"
#include "Const/Constant.h"
#include "Const/MapInfo.h"
#include <string>
#include "Network/Command.h"
#include <map>
USING_NS_CC;

class Record;
class HRocker;
class SoldierPath;
class ShopLayer;
class chat_client;
class Chatbox;
class PropertyPanel;

class HelloWorld : public cocos2d::Scene
{
	CC_SYNTHESIZE(INT32, _gameMode, GameMode);
	CC_SYNTHESIZE(INT32, _playerNumber, PlayerNumber);
	CC_SYNTHESIZE(ShopLayer*, _shop, Shop);
	CC_SYNTHESIZE(Record*, _labelRecord, LabelRecord);
	CC_SYNTHESIZE(Hero*, _myHero, MyHero);
	CC_SYNTHESIZE(Size, _visibleSize, VisibleSize);
	CC_SYNTHESIZE(Vec2, _origin, Origin);
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);
	CC_SYNTHESIZE(TMXTiledMap*, _map, Map);
	CC_SYNTHESIZE(MapInfo, _mapInformation, MapInformation);
	CC_SYNTHESIZE(Actor*, _blueShuiJin, BlueShuiJin);
	CC_SYNTHESIZE(Actor*, _redShuiJin, RedShuiJin);
	CC_SYNTHESIZE(Command, _command, Command);
	CC_SYNTHESIZE(PropertyPanel*, _propertyPanel, PropertyPanel);

public:
	//公开容器
	class chat_client* _client;
	Vector<Ref*> _actors;
	Vector<Actor*> _towers;
	Vector<Projectile*> _bullets;
	Vector<Hero*> _heroes;
	Vector<Soldier*> _soldiers;
	Map<float, Projectile*> _readyToLaunch;
	std::vector<Damage> _damages;

private:

	Sprite* _propertyPanelSwitch;
	Sprite* _chatboxSwitch;
	Chatbox* _chatbox;
	bool _isChatboxOpen;
	Sprite* _sprBG;
	SoldierPath* _blueSoldierPathPoints;
	SoldierPath* _redSoldierPathPoints;
	SoldierPath* _aiHeroPathPoints;
	void generateSoldiers(float delta);
	void selectSpriteForTouch(Point touchLocation);
	//初始化
	void initMapLayer();
	void initLabelRecord();
	void initHero(INT32 playerNumber, std::vector<HeroMessage> heroMessages);
	void initHRocker();
	void initSkillPanel();
	void initTower();
	void initListener();
	void initChatbox();
	void initPropertyPanel();
	//帧更新
	virtual void update(float delta);
	void TowerAttack();
	void updateHeroPosition();
	void updateBullets();
	void updateDamages();
	void updateSoldiersState();
	void clearObjects();
	void updateMap();
	//netWork
	int _frames;
	bool _gameBegin;
	std::map<int, bool> _isReady;
	void checkMap();
	//监听
	//监听器
	EventListenerTouchOneByOne* listenerTouch;
	EventListenerKeyboard* listenerKeyBoard;
	//鼠标点击事件
	virtual bool onTouchBegan(Touch* touch, Event* event);
	//按键事件
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event);
	//判断是否一直被按住
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	//鼠标监听器
	bool _isMouseSprite;
	Sprite* _mouseSprite;
	EventListenerMouse* listenerMouse;
	virtual bool onMouseMove(Event* event);
	void updateSkillPanel();
	bool gameEnd();
	void changeScene(float delta);
	void synchronize();
	void updateOtherHeroes(Command command);
	Vec2 getPositionInMap(const Vec2& mousePosition);

public:
	///TODO
    virtual bool init(INT32 playerNumber, chat_client* client, INT32 mode, std::vector<HeroMessage> heroMessages);
	virtual void initSpring();
	virtual void initShop();
	static HelloWorld* create(INT32 playerNumber, chat_client* client, INT32 mode, std::vector<HeroMessage> heroMessages);
};

#endif 
