#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Component/StateComponent.h"
#include "GameController/HRocker.h"
#include "Actor/Actor.h"
#include "../Component/Record.h"
#include "Component/ExpComponent.h"
#include "Actor/Projectile.h"
#include "Actor/Hero.h"
#include "GameController/HRocker.h"
#include "Hero/HouYi.h"

USING_NS_CC;


Scene* GameScene::createScene()
{
    return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameSceneScene.cpp\n");
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	
	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	loadingAnimation();
	initMapLayer();
	initHero();
	initLabelRecord();
	initHRocker();

	scheduleUpdate();
	for (int i = 0; i < 4; i++)
	{
		auto soldier = Soldier::create(EAttackMode::REMOTE, ECamp::BLUE, ERoad::MIDWAY, this);
		_map->addChild(soldier);
		soldier->setPosition(200, 200 + rand() % 100 * 10);
		soldier->setScale(0.3);
		_soldiers.pushBack(soldier);

	}

	//创建鼠标监听器
	listenerTouch = EventListenerTouchOneByOne::create();
	//绑定监听事件
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listenerTouch, 1);
	//创建键盘监听器
	listenerKeyBoard = EventListenerKeyboard::create();
	//绑定监听事件
	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(GameScene::onPressKey, this);
	listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(GameScene::onReleaseKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);

	listenerTouch->setSwallowTouches(false);

    return true;
}

void GameScene::generateSoldiers(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto soldier = Soldier::create(EAttackMode::MELEE, ECamp::BLUE, ERoad::DOWNWAY, this);
	soldier->setPosition(visibleSize / 4);
	soldier->setScale(0.1);
	soldier->setFirstDest(visibleSize);
	soldier->setSecondDest(visibleSize);
	_map->addChild(soldier);
	_soldiers.pushBack(soldier);
}
//初始化地图
void GameScene::initMapLayer()
{
	_map = TMXTiledMap::create("map/map1.tmx");
	auto size = _map->getBoundingBox().size;
	_map->setAnchorPoint(Vec2::ZERO);
	_map->setPosition(Vec2::ZERO);
//	_map->setScale(2);

	auto layerTower = _map->getLayer("Tower");
	layerTower->setVisible(false);

	addChild(_map, 0, TAG_MAP);
}
//初始化战绩面板
void GameScene::initLabelRecord()
{
	_labelRecord = Record::create();
	addChild(_labelRecord);
}
//初始化英雄
void GameScene::initHero()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_myHero = HouYi::create(this, ECamp::BLUE, "HouYi", EAttackMode::MELEE);
	_myHero->setPosition(visibleSize / 2);
	_myHero->setTag(TAG_MYHERO);
	_myHero->setScale(0.5);
	_myHero->setRecordComp(_labelRecord);
	_map->addChild(_myHero);
	_heros.pushBack(_myHero);
}
//初始化摇杆
void GameScene::initHRocker()
{
	_rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(200, 100));
	_rocker->startRocker(true);
	addChild(_rocker);
}
//加载动画
void GameScene::loadingAnimation()
{
	String heroName = "HouYi";

	auto animation_00 = Animation::create();
	animation_00->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	animation_00->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_00, StringUtils::format("%sMoveUp", heroName.getCString()));

	auto animation_01 = Animation::create();
	animation_01->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_01->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_01, StringUtils::format("%sMoveUpLeft", heroName.getCString()));

	auto animation_02 = Animation::create();
	animation_02->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight1.png", heroName.getCString(), heroName.getCString()));
	animation_02->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%supRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_02, StringUtils::format("%sMoveUpRight", heroName.getCString()));

	auto animation_03 = Animation::create();
	animation_03->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft1.png", heroName.getCString(), heroName.getCString()));
	animation_03->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sleft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_03, StringUtils::format("%sMoveLeft", heroName.getCString()));

	auto animation_04 = Animation::create();
	animation_04->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright1.png", heroName.getCString(), heroName.getCString()));
	animation_04->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sright2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_04, StringUtils::format("%sMoveRight", heroName.getCString()));

	auto animation_05 = Animation::create();
	animation_05->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown1.png", heroName.getCString(), heroName.getCString()));
	animation_05->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdown2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_05, StringUtils::format("%sMoveDown", heroName.getCString()));

	auto animation_06 = Animation::create();
	animation_06->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft1.png", heroName.getCString(), heroName.getCString()));
	animation_06->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownLeft2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_06, StringUtils::format("%sMoveDownLeft", heroName.getCString()));

	auto animation_07 = Animation::create();
	animation_07->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight1.png", heroName.getCString(), heroName.getCString()));
	animation_07->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sdownRight2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_07, StringUtils::format("%sMoveDownRight", heroName.getCString()));


	String skillAnimationName = "HouYiSkill2";
	auto skillAnimation = Animation::create();
	for (int i = 1; i < 5; ++i)
	{
		skillAnimation->addSpriteFrameWithFile(StringUtils::format("pictures/hero/HouYi/%s%d.png", skillAnimationName.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(skillAnimation, skillAnimationName.getCString());
}
//帧更新
void GameScene::update(float delta)
{
	updateHeroPosition();
	for (auto it=_bullets.begin();it!=_bullets.end();)
	{
		if (!(*it)->getTarget()->getAlreadyDead())
		{
			if ((*it)->calculateDistance() < (*it)->getTarget()->getBoundingBox().size.height / 2)
			{
				auto target = (*it)->getTarget();
				target->takeDamage((*it)->getDamage(), (*it)->getFromActor());
				removeChild(*it);
				it = _bullets.erase(it);
			}
			else
			{
				(*it)->calculatePosition();
				++it;
			}
		}
		else
		{
			removeChild(*it);
			it = _bullets.erase(it);
		}
	}

	for (auto it = _heros.begin(); it !=_heros.end(); ++it)
	{
		if ((*it)->getAlreadyDead())
		{
			(*it)->setVisible(false);
		}
	}
}

//更新英雄位置
void GameScene::updateHeroPosition()
{
	if (_rocker->getIsCanMove())
	{
		_myHero->setStandingAngle(_rocker->getAngle());
		_myHero->heroMove();
		auto movingSpeed = _myHero->getMoveSpeed();
		auto position = _map->getPosition();
		auto angle = _myHero->getStandingAngle();
		_map->setPosition(position - Vec2(cos(angle) * movingSpeed / 60, sin(angle) * movingSpeed / 60));
	}
	else
	{
		_myHero->stopMove();
	}
}
void GameScene::updateTowerAttackTarget()
{
}
void GameScene::updateSoldiersAttackTarget()
{


}


//测试
void GameScene::launch(float delta)
{
	auto from = dynamic_cast<Actor*>(getChildByTag(0));
	auto to = dynamic_cast<Actor*>(getChildByTag(1));
	
	if (from && !from->getAlreadyDead() && to && !to->getAlreadyDead())
	{
		auto bullet = Projectile::create(600, 10, from, to);
		addChild(bullet);
		_bullets.pushBack(bullet);
	}
}
//测试
void GameScene::test()
{
	auto animation = AnimationCache::getInstance()->getAnimation("YSMoveDownRight");
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	auto animate = Animate::create(animation);

	_myHero->runAction(RepeatForever::create(animate));
}

void GameScene::updateAttackTarget()
{
	updateTowerAttackTarget();
	updateSoldiersAttackTarget();
}

void GameScene::CircleDamage(Point point, float radius, float damage)
{
	

}


bool GameScene::onTouchBegan(Touch * touch, Event * event)
{
	auto nowTime = GetCurrentTime() / 1000;
	if (_myHero->getLastAttackTime() == 0)
	{
		_myHero->setLastAttackTime(nowTime);
	}

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_1))
	{
		_myHero->castSkill_1();
		keys[EventKeyboard::KeyCode::KEY_1] = false;

	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_2))
	{
		auto point = touch->getLocation();
		_myHero->castSkill_2(point);
		keys[EventKeyboard::KeyCode::KEY_2] = false;

	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_3))
	{
		auto point = touch->getLocation();
		_myHero->castSkill_3(point);
		keys[EventKeyboard::KeyCode::KEY_3] = false;

	}
	else
	{
		//不在攻击间隔内
		if (nowTime - _myHero->getLastAttackTime() > _myHero->getMinAttackInterval())
		{
			_myHero->updateAttackTarget();
			_myHero->attack();
		}
	}
	return true;
}

bool GameScene::onTouchMoved(Touch * touch, Event * event)
{
	return false;
}

bool GameScene::onTouchEnded(Touch * touch, Event * event)
{
	return false;
}



bool GameScene::onPressKey(EventKeyboard::KeyCode keyCode, Event * event)
{
	keys[keyCode] = true;
	return true;
}
bool GameScene::onReleaseKey(EventKeyboard::KeyCode keyCode, Event * event)
{
	//keys[keyCode] = false;

	return true;
}
bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (keys[keyCode])
	{
		return true;
	}
	else
	{
		return false;
	}
}