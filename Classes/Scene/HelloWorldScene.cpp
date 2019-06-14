#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Component/StateComponent.h"
#include "GameController/HRocker.h"
#include "Actor/Actor.h"
#include "../Component/Record.h"
#include "Component/ExpComponent.h"
#include "GameController/HRocker.h"
#include "Hero/HouYi.h"
#include "PathFind/SoldierPath.h"
#include "Actor/BuffProjectile.h"
#include "Hero/YaSe.h"
#include "Hero/DaJi.h"
#include "Actor/Spring.h"
#include "Scene/ShopLayer.h"
#include "StartGameScene.h"
#include "Hero/AIHero.h"

Scene* HelloWorld::createScene()
{
	return HelloWorld::create("", "");
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

HelloWorld* HelloWorld::create(const std::string& myHeroName, const std::string& aiHeroName)
{
	auto helloWorld = new(std::nothrow)HelloWorld;
	if (helloWorld && helloWorld->init(myHeroName, aiHeroName))
	{
		helloWorld->autorelease();
		return helloWorld;
	}
	CC_SAFE_DELETE(helloWorld);
	return nullptr;
}

bool HelloWorld::init(const std::string& myHeroName, const std::string& aiHeroName)
{
	if (!Scene::init())
	{
		return false;
	}

	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	//	test();

	initMapLayer();


	initMusic();
	initTower();
	initLabelRecord();
	initHero(myHeroName, aiHeroName);
	initHRocker();
	initListener();
	initSkillPanel();
	initSpring();
	initShop();
	initSurrenderMenu();

	schedule(schedule_selector(HelloWorld::generateSoldiers), 10.f, -1, 0.f);
	scheduleUpdate();

	//For test
	_myHero->setSkillPoint(2);
	//_myHero->skillLevelUp(1);
	//_myHero->skillLevelUp(2);
	//_myHero->skillLevelUp(3);
	_myHero->setCalmTime_1(3);
	//

	return true;
}

void HelloWorld::initMusic()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/Welcome.wav", false, 1, 0, 1.2);

}
void HelloWorld::initSpring()
{
	auto size = _map->getBoundingBox().size;

	auto blueSpring = Spring::create(this, ECamp::BLUE);
	blueSpring->setPosition(BLUE_HERO_BIRTHPLACE);
	blueSpring->setScale(0.3);
	blueSpring->setScale(1.5);
	_map->addChild(blueSpring);

	auto redSpring = Spring::create(this, ECamp::RED);
	redSpring->setPosition(RED_HERO_BIRTHPLACE);
	redSpring->setScale(0.3);
	redSpring->setScale(1.5);
	_map->addChild(redSpring);
}

void HelloWorld::initSurrenderMenu()
{
	auto surrenderMenu = MenuItemImage::create(
		"pictures/others/surrender.png",
		"pictures/others/surrender1.png",
		CC_CALLBACK_1(HelloWorld::menuSurrenderCallBack, this)
	);
	surrenderMenu->setPosition(Vec2(1165.5, 720 - 49.5));
	addChild(surrenderMenu);
}

void HelloWorld::initShop()
{
	_shop = ShopLayer::create();
	_shop->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_shop->setPosition(_visibleSize / 2);
	_shop->setVisible(false);
	addChild(_shop);
}




void HelloWorld::initMapLayer()
{
	_sprBG = Sprite::create("pictures/others//BG.png");
	_sprBG->setAnchorPoint(Vec2(0, 0.5));
	_sprBG->setPosition(Vec2(-1000, 360));
	addChild(_sprBG);

	_map = TMXTiledMap::create("map/map2.tmx");
	auto size = _map->getBoundingBox().size;
	_map->setAnchorPoint(Vec2::ZERO);
	_map->setPosition(Vec2::ZERO);

	auto wallLayer = _map->getLayer("Wall");
	wallLayer->setZOrder(0);

	_mapInformation = MapInfo(_map);
	_blueSoldierPathPoints = SoldierPath::create("Data/BluePathPoints.txt", _mapInformation);
	_redSoldierPathPoints = SoldierPath::create("Data/RedPathPoints.txt", _mapInformation);
	_aiHeroPathPoints = SoldierPath::create("Data/AIHeroPathPoints.txt", _mapInformation);
	_actors.pushBack(_blueSoldierPathPoints);
	_actors.pushBack(_redSoldierPathPoints);
	_actors.pushBack(_aiHeroPathPoints);

	auto collisionLayer = _map->getLayer("collision");
	collisionLayer->setVisible(false);

	addChild(_map, 0, TAG_MAP);
}

void HelloWorld::initLabelRecord()
{
	_labelRecord = Record::create();
	addChild(_labelRecord);
}

void HelloWorld::initHero(const std::string& myHeroName, const std::string& aiHeroName)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (myHeroName == "YaSe")
	{
		_myHero = YaSe::create(this, ECamp::BLUE, myHeroName, EAttackMode::MELEE);
	}
	else if (myHeroName == "DaJi")
	{
		_myHero = DaJi::create(this, ECamp::BLUE, myHeroName, EAttackMode::REMOTE);
	}
	else
	{
		_myHero = HouYi::create(this, ECamp::BLUE, myHeroName, EAttackMode::REMOTE);
	}
	_myHero->setPosition(Size(1280, 720) - visibleSize / 2);
	_myHero->setTag(TAG_MYHERO);
	_myHero->setScale(0.5);
	_myHero->setRecordComp(_labelRecord);
	_map->addChild(_myHero);
	_myHero->setZOrder(1);
	_myHero->getRecordComp()->setVisible(true);
	_map->setPosition(visibleSize / 2 - (Size)_myHero->getPosition());
	_heroes.pushBack(_myHero);
	_actors.pushBack(_myHero);

	AIHero* aiHero;
	if (aiHeroName == "YaSe")
	{
		aiHero = AIHero::create(this, ECamp::RED, aiHeroName, EAttackMode::MELEE, _aiHeroPathPoints);
	}
	else
	{
		aiHero = AIHero::create(this, ECamp::RED, aiHeroName, EAttackMode::REMOTE, _aiHeroPathPoints);
	}
	aiHero->setPosition(Size(6400, 720) - visibleSize / 2);
	aiHero->setScale(0.5);
	_map->addChild(aiHero);
	aiHero->setZOrder(1);
	_heroes.pushBack(aiHero);
	_actors.pushBack(aiHero);

	auto labelDie = Label::create("Reborn in 0 seconds", "fonts/HELVETICAEXT-NORMAL.TTF", 100);
	labelDie->setPosition(visibleSize / 2);
	labelDie->setVisible(false);
	labelDie->setTag(TAG_DIE);
	addChild(labelDie);

}

void HelloWorld::initHRocker()
{
	_rocker = HRocker::createHRocker("pictures/others/rocker.png", "pictures/others/rockerBG.png", Vec2(200, 100));
	_rocker->startRocker(true);
	addChild(_rocker);
}

void HelloWorld::initTower()
{
	auto redTower = Actor::create("pictures/building/redTower.png", this, ECamp::RED);
	redTower->setPosition(RED_TOWER_POSITION);
	redTower->setScale(0.7);
	_map->addChild(redTower);
	_towers.pushBack(redTower);
	_actors.pushBack(redTower);

	auto blueTower = Actor::create("pictures/building/blueTower.png", this, ECamp::BLUE);
	blueTower->setPosition(BLUE_TOWER_POSITION);
	blueTower->setScale(0.7);
	_map->addChild(blueTower);
	_towers.pushBack(blueTower);
	_actors.pushBack(blueTower);

	_blueShuiJin = Actor::create("pictures/building/blueShuiJin.png", this, ECamp::BLUE);
	_blueShuiJin->setPosition(BLUE_SHUIJIN_POSITION);
	_blueShuiJin->getHealthComp()->changeMaxTo(16000);
	_blueShuiJin->setScale(0.7);
	_map->addChild(_blueShuiJin);
	_towers.pushBack(_blueShuiJin);
	_actors.pushBack(_blueShuiJin);

	_redShuiJin = Actor::create("pictures/building/redShuiJin.png", this, ECamp::RED);
	_redShuiJin->setPosition(RED_SHUIJIN_POSITION);
	_redShuiJin->getHealthComp()->changeMaxTo(16000);
	_redShuiJin->setScale(0.7);
	_map->addChild(_redShuiJin);
	_towers.pushBack(_redShuiJin);
	_actors.pushBack(_redShuiJin);
}

void HelloWorld::initListener()
{
	//创建触摸监听器
	listenerTouch = EventListenerTouchOneByOne::create();
	//绑定监听事件
	listenerTouch->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listenerTouch, 1);
	//创建键盘监听器
	listenerKeyBoard = EventListenerKeyboard::create();
	//绑定监听事件
	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onPressKey, this);
	listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onReleaseKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
	//鼠标监听器
	_isMouseSprite = false;
	_mouseSprite = Sprite::create("pictures/others/mouseSprite.png");
	_mouseSprite->setVisible(false);
	this->addChild(_mouseSprite);
	listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listenerMouse, 2);
	listenerTouch->setSwallowTouches(false);
}

void HelloWorld::update(float delta)
{
	if (!gameEnd())
	{
		TowerAttack();
		updateHeroPosition();
		updateBullets();
		updateDamages();
		updateSoldiersState();
		updateSkillPanel();
		clearObjects();
	}
}

void HelloWorld::clearObjects()
{
	auto nowTime = GetCurrentTime() / 1000.f;

	for (auto it = _heroes.begin(); it != _heroes.end(); ++it)
	{
		if ((*it)->getAlreadyDead())
		{
			if ((*it)->getResurgenceTime() <= nowTime)
			{
				(*it)->reborn();

				if ((*it) == _myHero)
				{
					_map->setPosition(_visibleSize / 2 - static_cast<Size>(_myHero->getPosition()));
					getChildByTag(TAG_DIE)->setVisible(false);
				}
			}
			else if ((*it) == _myHero)
			{
				auto labelDie = dynamic_cast<Label*>(getChildByTag(TAG_DIE));
				labelDie->setVisible(true);
				labelDie->setString(StringUtils::format("%d", static_cast<INT32>(_myHero->getResurgenceTime() - GetCurrentTime() / 1000.f)));
			}
		}
		else
		{
			(*it)->clearBuff();
		}
	}

	for (auto it = _soldiers.begin(); it != _soldiers.end();)
	{

		if ((*it)->getAlreadyDead())
		{
			_map->removeChild(*it);
			(*it)->getHealthComp()->unscheduleAllSelectors();
			it = _soldiers.erase(it);
		}
		else
		{
			(*it)->clearBuff();
			++it;
		}
	}

	for (auto it = _towers.begin(); it != _towers.end();)
	{
		if ((*it)->getAlreadyDead())
		{
			_map->removeChild(*it);
			(*it)->getHealthComp()->unscheduleAllSelectors();
			_mapInformation.removeTowerCollision((*it)->getPosition());
			it = _towers.erase(it);
		}
		else
		{
			(*it)->clearBuff();
			++it;
		}
	}
}

void HelloWorld::TowerAttack()
{
	for (auto it = _towers.begin(); it != _towers.end(); ++it)
	{
		(*it)->attack();
	}
}

void HelloWorld::updateBullets()
{
	auto nowTime = GetCurrentTime() / 1000.f;

	for (auto it = _readyToLaunch.begin(); it != _readyToLaunch.end();)
	{
		if ((*it).first <= nowTime)
		{
			if (!(*it).second->getTarget()->getAlreadyDead() && !(*it).second->getFromActor()->getAlreadyDead())
			{
				(*it).second->setPosition((*it).second->getFromActor()->getPosition());
				_map->addChild((*it).second);
				_bullets.pushBack((*it).second);
			}
			it = _readyToLaunch.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = _bullets.begin(); it != _bullets.end();)
	{
		if (!(*it)->getTarget()->getAlreadyDead())
		{
			if ((*it)->calculateDistance() < (*it)->getTarget()->getBoundingBox().size.height / 2)
			{
				auto target = (*it)->getTarget();
				target->takeDamage(EDamageType::PHYSICS_DAMAGE, (*it)->getDamage(), (*it)->getFromActor());
				_map->removeChild(*it);
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
			_map->removeChild(*it);
			it = _bullets.erase(it);
		}
	}

	auto tmpSpr = this->getMap()->getChildByTag(TAG_DAJI_SKILL2);
	auto daJiBuffProjectile = dynamic_cast<Projectile*>(tmpSpr);
	//妲己的二技能飞行物
	if (daJiBuffProjectile)
	{
		if (!daJiBuffProjectile->getTarget()->getAlreadyDead())
		{
			if (daJiBuffProjectile->calculateDistance() < daJiBuffProjectile->getTarget()->getBoundingBox().size.height / 2)
			{
				auto target = daJiBuffProjectile->getTarget();
				target->takeDamage(EDamageType::MAGIC_DAMAGE, daJiBuffProjectile->getDamage(), daJiBuffProjectile->getFromActor());
				auto buff = Buff::create(EBuffType::VERTIGO, 1.5, 0, 0, -60, 0, 0, 0, 0, 0, 0);
				target->takeBuff(buff);
				_map->removeChild(daJiBuffProjectile);
			}
			else
			{
				daJiBuffProjectile->calculatePosition();
			}
		}
		else
		{
			_map->removeChild(daJiBuffProjectile);
		}
	}
}

void HelloWorld::updateDamages()
{
	for (auto it = _damages.begin(); it != _damages.end();)
	{
		auto nowTime = GetCurrentTime() / 1000.f;

		if (it->_actionTime <= nowTime)
		{
			if (!it->_target->getAlreadyDead())
			{
				it->_target->takeDamage(it->_damageType, it->_damage, it->_instiogator);
			}

			it = _damages.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void HelloWorld::updateSoldiersState()
{
	for (auto& i : _soldiers)
	{
		if (!i->getAlreadyDead())
		{
			i->updateState();
		}
	}

	for (auto& i : _heroes)
	{
		auto aiHero = dynamic_cast<AIHero*>(i);
		if (aiHero && !aiHero->getAlreadyDead())
		{
			aiHero->updateState();
		}
	}
}

void HelloWorld::updateHeroPosition()
{
	if (_rocker->getIsCanMove() && !_myHero->getAlreadyDead())
	{
		_myHero->setStandingAngle(_rocker->getAngle());
		auto positionDelta = MyMath::calculatePositionDelta(_myHero->getStandingAngle(), _myHero->getMoveSpeed());
		auto newPosition = _myHero->getPosition() + positionDelta;
		if (_mapInformation.checkCollision(newPosition))
		{
			_myHero->heroMove();
			if (GetCurrentTime() / 1000.f - _myHero->getLastAttackTime() > _myHero->getMinAttackInterval())
			{
				_map->setPosition(_map->getPosition() - positionDelta);
				_sprBG->setPosition(_sprBG->getPosition() - positionDelta);
			}
		}
	}
	else
	{
		_myHero->stopMove();
	}
}

void HelloWorld::generateSoldiers(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto soldier_1 = Soldier::create(this, EAttackMode::MELEE, ECamp::BLUE, ERoad::DOWNWAY, _blueSoldierPathPoints);
	soldier_1->setPosition(visibleSize / 4 + Size(200, 0));
	soldier_1->setNextDest(_blueSoldierPathPoints->getNextPoint(soldier_1->getPosition()));
	soldier_1->setScale(1.5);
	_map->addChild(soldier_1);
	_soldiers.pushBack(soldier_1);
	_actors.pushBack(soldier_1);

	auto soldier_2 = Soldier::create(this, EAttackMode::MELEE, ECamp::BLUE, ERoad::DOWNWAY, _blueSoldierPathPoints);
	soldier_2->setPosition(visibleSize / 4 + Size(100, 0));
	soldier_2->setNextDest(_blueSoldierPathPoints->getNextPoint(soldier_2->getPosition()));
	soldier_2->setScale(1.5);
	_map->addChild(soldier_2);
	_soldiers.pushBack(soldier_2);
	_actors.pushBack(soldier_2);

	auto soldier_4 = Soldier::create(this, EAttackMode::REMOTE, ECamp::BLUE, ERoad::DOWNWAY, _blueSoldierPathPoints);
	soldier_4->setPosition(visibleSize / 4);
	soldier_4->setNextDest(_blueSoldierPathPoints->getNextPoint(soldier_4->getPosition()));
	soldier_4->setScale(1.5);
	_map->addChild(soldier_4);
	_soldiers.pushBack(soldier_4);
	_actors.pushBack(soldier_4);

	auto soldier_5 = Soldier::create(this, EAttackMode::MELEE, ECamp::RED, ERoad::DOWNWAY, _redSoldierPathPoints);
	soldier_5->setPosition(Size(6200, 360) - visibleSize / 4);
	soldier_5->setNextDest(_redSoldierPathPoints->getNextPoint(soldier_5->getPosition()));
	soldier_5->setScale(1.5);
	_map->addChild(soldier_5);
	_soldiers.pushBack(soldier_5);
	_actors.pushBack(soldier_5);

	auto soldier_6 = Soldier::create(this, EAttackMode::MELEE, ECamp::RED, ERoad::DOWNWAY, _redSoldierPathPoints);
	soldier_6->setPosition(Size(6300, 360) - visibleSize / 4);
	soldier_6->setNextDest(_redSoldierPathPoints->getNextPoint(soldier_6->getPosition()));
	soldier_6->setScale(1.5);
	_map->addChild(soldier_6);
	_soldiers.pushBack(soldier_6);
	_actors.pushBack(soldier_6);

	auto soldier_8 = Soldier::create(this, EAttackMode::REMOTE, ECamp::RED, ERoad::DOWNWAY, _redSoldierPathPoints);
	soldier_8->setPosition(Size(6400, 360) - visibleSize / 4);
	soldier_8->setNextDest(_redSoldierPathPoints->getNextPoint(soldier_8->getPosition()));
	soldier_8->setScale(1.5);
	_map->addChild(soldier_8);
	_soldiers.pushBack(soldier_8);
	_actors.pushBack(soldier_8);
}

void HelloWorld::selectSpriteForTouch(Point touchLocation)
{
	auto sprPlus_1 = getChildByTag(TAG_SPRPLUS_1);
	auto tmp = sprPlus_1;
	auto sprPlus_2 = getChildByTag(TAG_SPRPLUS_2);
	auto sprPlus_3 = getChildByTag(TAG_SPRPLUS_3);
	if (sprPlus_1->isVisible() && sprPlus_1->getBoundingBox().containsPoint(touchLocation))
	{
		_myHero->skillLevelUp(1);
	}
	else if (sprPlus_2->isVisible() && sprPlus_2->getBoundingBox().containsPoint(touchLocation))
	{
		_myHero->skillLevelUp(2);
	}
	else if (sprPlus_3->isVisible() && sprPlus_3->getBoundingBox().containsPoint(touchLocation))
	{
		_myHero->skillLevelUp(3);
	}
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * event)
{
	//log("touch(%f,%f)", touch->getLocation().x, touch->getLocation().y);

	//启动装备面板
	if (_shop->isVisible())
	{
		Equipment* equip;
		INT32 no;
		if ((equip = _shop->getNumberOfEquip(touch->getLocation())) != nullptr)
		{
			if (getLabelRecord()->getMoney() >= equip->getGoldToBuy())
			{
				_shop->getEquip(equip);
				_myHero->getEquip(equip);
				//		log("%f", _myHero->getMoveSpeed());
			}
		}
		else if ((no = _shop->removeEquip(touch->getLocation())) != -1)
		{
			_myHero->sellEquip(no);
		}
		else if (_shop->checkForExit(touch->getLocation()))
		{
			_shop->setVisible(false);
		}
		return false;
	}
	else if (getLabelRecord()->getSprGold()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		_shop->setVisible(true);
		return false;
	}

	//交互技能面板
	Point touchLocation = Vec2(touch->getLocation().x, touch->getLocation().y);
	this->selectSpriteForTouch(touchLocation);

	//释放攻击/技能
	auto nowTime = GetCurrentTime() / 1000.f;
	if (_isMouseSprite)
	{
		_isMouseSprite = false;
		_mouseSprite->setVisible(false);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_1) && _myHero->checkSkillStatus(1))
	{
		auto daJi = dynamic_cast<DaJi*>(_myHero);
		if (daJi)
		{
			auto point = touch->getLocation();
			_myHero->castSkill_1(point);
			keys[EventKeyboard::KeyCode::KEY_1] = false;
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_2) && _myHero->checkSkillStatus(2))
	{
		auto houYi = dynamic_cast<HouYi*>(_myHero);
		if (houYi)
		{
			auto point = touch->getLocation();
			_myHero->castSkill_2(point);
			keys[EventKeyboard::KeyCode::KEY_2] = false;
		}

	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_3) && _myHero->checkSkillStatus(3))
	{
		auto houYi = dynamic_cast<HouYi*>(_myHero);
		if (houYi)
		{
			auto point = touch->getLocation();
			_myHero->castSkill_3(point);
			keys[EventKeyboard::KeyCode::KEY_3] = false;
		}

	}
	else
	{
		//不在攻击间隔内
		if (nowTime - _myHero->getLastAttackTime() > _myHero->getMinAttackInterval())
		{
			_myHero->attack();
		}
	}
	return true;
}

bool HelloWorld::onPressKey(EventKeyboard::KeyCode keyCode, Event * event)
{
	auto houYi = dynamic_cast<HouYi*>(_myHero);
	if (houYi)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_1 && houYi->checkSkillStatus(1))
		{
			_myHero->castSkill_1();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_2 && houYi->checkSkillStatus(2))
		{
			_isMouseSprite = true;
			_mouseSprite->setVisible(true);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_3 && houYi->checkSkillStatus(3))
		{
			_isMouseSprite = true;
			_mouseSprite->setVisible(true);
		}
	}
	auto yaSe = dynamic_cast<YaSe*>(_myHero);
	if (yaSe)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_1 && yaSe->checkSkillStatus(1))
		{
			_myHero->castSkill_1();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_2 && yaSe->checkSkillStatus(2))
		{
			_myHero->castSkill_2();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_3 && yaSe->checkSkillStatus(3))
		{
			_myHero->castSkill_3();
		}
	}
	auto daJi = dynamic_cast<DaJi*>(_myHero);
	if (daJi)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_1 && daJi->checkSkillStatus(1))
		{
			_isMouseSprite = true;
			_mouseSprite->setVisible(true);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_2 && daJi->checkSkillStatus(2))
		{
			_myHero->castSkill_2();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_3 && daJi->checkSkillStatus(3))
		{
			_myHero->castSkill_3();
		}
	}
	keys[keyCode] = true;
	return true;
}

bool HelloWorld::onReleaseKey(EventKeyboard::KeyCode keyCode, Event * event)
{
	auto houYi = dynamic_cast<HouYi*>(_myHero);
	if (houYi)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_1)
		{
			keys[keyCode] = false;
		}
	}
	auto yaSe = dynamic_cast<YaSe*>(_myHero);
	if (yaSe)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_1 || keyCode == EventKeyboard::KeyCode::KEY_3 || keyCode == EventKeyboard::KeyCode::KEY_2)
		{
			keys[keyCode] = false;
		}
	}
	auto daJi = dynamic_cast<DaJi*>(_myHero);
	if (daJi)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_2 || keyCode == EventKeyboard::KeyCode::KEY_3)
		{
			keys[keyCode] = false;
		}
	}
	//keys[keyCode] = false;

	return true;
}

bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode keyCode)
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

bool HelloWorld::onMouseMove(Event * ee)
{
	auto e = dynamic_cast<EventMouse*>(ee);
	auto ex = e->getCursorX();
	auto ey = e->getCursorY();
	_mouseSprite->setPosition(Vec2(ex, ey));
	//	log("Mouse(%f,%f)", ex, ey);

	return true;
}

void HelloWorld::updateSkillPanel()
{
	auto nowTime = GetCurrentTime() / 1000.f;
	auto heroName = _myHero->getHeroName();
	auto skillPoints = _myHero->getSkillPoint();

	auto skillTime_1 = _myHero->getCalmTime_1() + _myHero->getLastSkillTime_1();
	auto skillTime_2 = _myHero->getCalmTime_2() + _myHero->getLastSkillTime_2();
	auto skillTime_3 = _myHero->getCalmTime_3() + _myHero->getLastSkillTime_3();

	auto skillLevel_1 = _myHero->getSkillLevel_1();
	auto skillLevel_2 = _myHero->getSkillLevel_2();
	auto skillLevel_3 = _myHero->getSkillLevel_3();

	auto sprSkill_1 = dynamic_cast<Sprite*>(getChildByTag(TAG_SPRSKILL_1));
	auto sprSkill_2 = dynamic_cast<Sprite*>(getChildByTag(TAG_SPRSKILL_2));
	auto sprSkill_3 = dynamic_cast<Sprite*>(getChildByTag(TAG_SPRSKILL_3));
	auto sprPlus_1 = dynamic_cast<Sprite*>(getChildByTag(TAG_SPRPLUS_1));
	auto sprPlus_2 = dynamic_cast<Sprite*>(getChildByTag(TAG_SPRPLUS_2));
	auto sprPlus_3 = dynamic_cast<Sprite*>(getChildByTag(TAG_SPRPLUS_3));
	//For test
	if (skillLevel_2 != 0)
	{
		int a = 1;
	}

	if (skillLevel_1 == 0 || skillTime_1 >= nowTime)
	{
		sprSkill_1->setTexture(StringUtils::format("pictures//hero//%s//%sSkill11.png", heroName.getCString(), heroName.getCString()));
	}
	else
	{
		sprSkill_1->setTexture(StringUtils::format("pictures//hero//%s//%sSkill1.png", heroName.getCString(), heroName.getCString()));
	}

	if (skillLevel_2 == 0 || skillTime_2 >= nowTime)
	{
		sprSkill_2->setTexture(StringUtils::format("pictures//hero//%s//%sSkill21.png", heroName.getCString(), heroName.getCString()));
	}
	else
	{
		sprSkill_2->setTexture(StringUtils::format("pictures//hero//%s//%sSkill2.png", heroName.getCString(), heroName.getCString()));
	}

	if (skillLevel_3 == 0 || skillTime_3 >= nowTime)
	{
		sprSkill_3->setTexture(StringUtils::format("pictures//hero//%s//%sSkill31.png", heroName.getCString(), heroName.getCString()));
	}
	else
	{
		sprSkill_3->setTexture(StringUtils::format("pictures//hero//%s//%sSkill3.png", heroName.getCString(), heroName.getCString()));
	}

	if (skillPoints)
	{
		if (_myHero->getSkillLevel_1() < 3)
		{
			sprPlus_1->setVisible(true);
		}
		else
		{
			sprPlus_1->setVisible(false);
		}
		if (_myHero->getSkillLevel_2() < 3)
		{
			sprPlus_2->setVisible(true);
		}
		else
		{
			sprPlus_2->setVisible(false);
		}
		if (_myHero->getSkillLevel_3() < 3)
		{
			sprPlus_3->setVisible(true);
		}
		else
		{
			sprPlus_3->setVisible(false);
		}
	}
	else
	{
		sprPlus_1->setVisible(false);
		sprPlus_2->setVisible(false);
		sprPlus_3->setVisible(false);
	}

}

bool HelloWorld::gameEnd()
{
	if (_blueShuiJin->getAlreadyDead())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/Defeat.wav", false, 1, 0, 1.5);

		unscheduleUpdate();
		_eventDispatcher->removeAllEventListeners();
		auto sprDefeated = Sprite::create("pictures/others/defeate.png");
		sprDefeated->setPosition(_visibleSize / 2);
		addChild(sprDefeated);
		scheduleOnce(schedule_selector(HelloWorld::changeScene), 5.f);
		return true;
	}
	else if (_redShuiJin->getAlreadyDead())
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/Victory.wav", false, 1, 0, 1.5);
		unscheduleUpdate();
		_eventDispatcher->removeAllEventListeners();
		auto sprVictory = Sprite::create("pictures/others/victory.png");
		sprVictory->setPosition(_visibleSize / 2);
		addChild(sprVictory);
		scheduleOnce(schedule_selector(HelloWorld::changeScene), 5.f);
		return true;
	}

	return false;
}

void HelloWorld::changeScene(float delta)
{
	auto nextScene = StartGame::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
}

void HelloWorld::menuSurrenderCallBack(cocos2d::Ref * pSender)
{
	_blueShuiJin->setAlreadyDead(true);
	//gameEnd();
}

void HelloWorld::initSkillPanel()
{
	String heroName = _myHero->getHeroName();

	auto sprSkill_1 = Sprite::create(StringUtils::format("pictures//hero//%s//%sSkill11.png", heroName.getCString(), heroName.getCString()));
	sprSkill_1->setPosition(Vec2(949, 88));
	sprSkill_1->setTag(TAG_SPRSKILL_1);
	addChild(sprSkill_1);

	auto sprSkill_2 = Sprite::create(StringUtils::format("pictures//hero//%s//%sSkill21.png", heroName.getCString(), heroName.getCString()));
	sprSkill_2->setPosition(Vec2(1027, 222));
	sprSkill_2->setTag(TAG_SPRSKILL_2);
	addChild(sprSkill_2);

	auto sprSkill_3 = Sprite::create(StringUtils::format("pictures//hero//%s//%sSkill31.png", heroName.getCString(), heroName.getCString()));
	sprSkill_3->setPosition(Vec2(1161.5, 298.5));
	sprSkill_3->setTag(TAG_SPRSKILL_3);
	addChild(sprSkill_3);

	auto sprPlus_1 = Sprite::create("pictures//others//SkillLevelUp.png");
	sprPlus_1->setPosition(870.0, 151.0);
	sprPlus_1->setTag(TAG_SPRPLUS_1);
	sprPlus_1->setVisible(false);
	addChild(sprPlus_1);

	auto sprPlus_2 = Sprite::create("pictures//others//SkillLevelUp.png");
	sprPlus_2->setPosition(959.0, 290.0);
	sprPlus_2->setTag(TAG_SPRPLUS_2);
	sprPlus_2->setVisible(false);
	addChild(sprPlus_2);

	auto sprPlus_3 = Sprite::create("pictures//others//SkillLevelUp.png");
	sprPlus_3->setPosition(1095, 367.0);
	sprPlus_3->setTag(TAG_SPRPLUS_3);
	sprPlus_3->setVisible(false);
	addChild(sprPlus_3);

}
