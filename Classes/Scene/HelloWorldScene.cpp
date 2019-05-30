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

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	
	//test();

	initMapLayer();

	loadingAnimation();
	initTower();
	initLabelRecord();
	initHero();
	initHRocker();
	initSkillPanel();

	schedule(schedule_selector(HelloWorld::generateSoldiers), 10.f, -1, 0.f);

	scheduleUpdate();

	return true;
}

void HelloWorld::initMapLayer()
{
	_map = TMXTiledMap::create("map/map2.tmx");
	auto size = _map->getBoundingBox().size;
	_map->setAnchorPoint(Vec2::ZERO);
	log("%f", size.height);
	_map->setPosition(Vec2::ZERO);

	auto wallLayer = _map->getLayer("Wall");
	wallLayer->setZOrder(0);

	_mapInformation = MapInfo(_map);
	_soldierPathPoints = SoldierPath::create("A:/major/exedir/wzry/Data/PathPoints.txt", _mapInformation);
	_actors.pushBack(_soldierPathPoints);

	auto collisionLayer = _map->getLayer("collision");
	collisionLayer->setVisible(false);

	addChild(_map, 0, TAG_MAP);
}

void HelloWorld::initLabelRecord()
{
	_labelRecord = Record::create();
	addChild(_labelRecord);
}

void HelloWorld::initHero()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_myHero = HouYi::create(this, ECamp::BLUE, "HouYi", EAttackMode::REMOTE);
	log("HP: %d", _myHero->getHealthComp()->getMaxState());
	_myHero->setPosition(visibleSize / 2);
	_myHero->setTag(TAG_MYHERO);
	_myHero->setScale(0.5);
	_myHero->setRecordComp(_labelRecord);
	_map->addChild(_myHero);
	_myHero->setZOrder(1);
	_heroes.pushBack(_myHero);
	_actors.pushBack(_myHero);


	auto labelDie = Label::create("D I E", "fonts/HELVETICAEXT-NORMAL.TTF", 100);
	labelDie->setPosition(visibleSize / 2);
	labelDie->setVisible(false);
	labelDie->setTag(TAG_DIE);
	addChild(labelDie);
}

void HelloWorld::initHRocker()
{
	_rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(200, 100));
	_rocker->startRocker(true);
	addChild(_rocker);
}

void HelloWorld::initSkillPanel()
{
	//添加技能面板
	auto sprSkill_1 = Sprite::create();
}

void HelloWorld::loadingAnimation()
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



	String soldierType = "BlueMelee";

	auto animation_51 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_51->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_51, StringUtils::format("%sMoveUp", soldierType.getCString()));

	auto animation_52 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_52->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_52, StringUtils::format("%sMoveDown", soldierType.getCString()));

	auto animation_53 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_53->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_53, StringUtils::format("%sMoveLeft", soldierType.getCString()));

	auto animation_54 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_54->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_54, StringUtils::format("%sMoveRight", soldierType.getCString()));

	auto animation_55 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_55->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_55->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_55, StringUtils::format("%sAttackUp", soldierType.getCString()));

	auto animation_56 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_56->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_56->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_56, StringUtils::format("%sAttackDown", soldierType.getCString()));

	auto animation_57 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_57->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_57->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_57, StringUtils::format("%sAttackLeft", soldierType.getCString()));

	auto animation_58 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_58->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_58->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_58, StringUtils::format("%sAttackRight", soldierType.getCString()));


	soldierType = "BlueRemote";

	auto animation_59 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_59->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_59, StringUtils::format("%sMoveUp", soldierType.getCString()));

	auto animation_60 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_60->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_60, StringUtils::format("%sMoveDown", soldierType.getCString()));

	auto animation_61 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_61->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_61, StringUtils::format("%sMoveLeft", soldierType.getCString()));

	auto animation_62 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_62->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	AnimationCache::getInstance()->addAnimation(animation_62, StringUtils::format("%sMoveRight", soldierType.getCString()));

	auto animation_63 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_63->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackUp%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_63->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sUp1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_63, StringUtils::format("%sAttackUp", soldierType.getCString()));

	auto animation_64 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_64->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackDown%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_64->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sDown1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_64, StringUtils::format("%sAttackDown", soldierType.getCString()));

	auto animation_65 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_65->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackLeft%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_65->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sLeft1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_65, StringUtils::format("%sAttackLeft", soldierType.getCString()));

	auto animation_66 = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		animation_66->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sAttackRight%d.png", soldierType.getCString(), soldierType.getCString(), i));
	}
	animation_66->addSpriteFrameWithFile(StringUtils::format("pictures\\soldier\\%s\\%sRight1.png", soldierType.getCString(), soldierType.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_66, StringUtils::format("%sAttackRight", soldierType.getCString()));

}

void HelloWorld::initTower()
{
	auto tower = Actor::create(this, ECamp::RED);
	tower->setPosition(RED_TOWER_POSITION);
	tower->setScale(0.7);
	_map->addChild(tower);
	_towers.pushBack(tower);
	_actors.pushBack(tower);
}

void HelloWorld::update(float delta)
{
	TowerAttack();

	updateHeroPosition();

	updateBullets();

	updateDamages();

	updateSoldiersState();

	clearObjects();
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
					_map->setPosition(Vec2::ZERO);
					getChildByTag(TAG_DIE)->setVisible(false);
				}
			}
			else if ((*it) == _myHero)
			{
				getChildByTag(TAG_DIE)->setVisible(true);
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

void HelloWorld::test()
{
	ValueMap data;
	ValueVector p;
	for (int i = 0; i < 4; ++i)
	{
		p.push_back(Value(5.0));
	}
	data["CD"] = p;
	data["MP"] = p;
	FileUtils::getInstance()->writeValueMapToFile(data, "D:\\LatestFiles\\hello\\Data\\data.plist");
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
}

void HelloWorld::updateHeroPosition()
{
	if (_rocker->getIsCanMove())
	{
		_myHero->setStandingAngle(_rocker->getAngle());
		auto positionDelta = MyMath::calculatePositionDelta(_myHero->getStandingAngle(),_myHero->getMoveSpeed());
		auto newPosition = _myHero->getPosition() + positionDelta;
		if (_mapInformation.checkCollision(newPosition))
		{
			_myHero->heroMove();
			_map->setPosition(_map->getPosition() - positionDelta);
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

	auto soldier_1 = Soldier::create(this, EAttackMode::MELEE, ECamp::BLUE, ERoad::DOWNWAY, _soldierPathPoints);
	soldier_1->setPosition(visibleSize / 4);
	soldier_1->setNextDest(_soldierPathPoints->getNextPoint(soldier_1->getPosition()));
	soldier_1->setScale(1.5);
	_map->addChild(soldier_1);
	_soldiers.pushBack(soldier_1);
	_actors.pushBack(soldier_1);

	auto soldier_2 = Soldier::create(this, EAttackMode::MELEE, ECamp::BLUE, ERoad::DOWNWAY, _soldierPathPoints);
	soldier_2->setPosition(visibleSize / 4 + Size(0, 30));
	soldier_2->setNextDest(_soldierPathPoints->getNextPoint(soldier_2->getPosition()));
	soldier_2->setScale(1.5);
	_map->addChild(soldier_2);
	_soldiers.pushBack(soldier_2);
	_actors.pushBack(soldier_2);

	auto soldier_3 = Soldier::create(this, EAttackMode::MELEE, ECamp::BLUE, ERoad::DOWNWAY, _soldierPathPoints);
	soldier_3->setPosition(visibleSize / 4 + Size(0, 60));
	soldier_3->setNextDest(_soldierPathPoints->getNextPoint(soldier_3->getPosition()));
	soldier_3->setScale(1.5);
	_map->addChild(soldier_3);
	_soldiers.pushBack(soldier_3);
	_actors.pushBack(soldier_3);

	auto soldier_4 = Soldier::create(this, EAttackMode::REMOTE, ECamp::BLUE, ERoad::DOWNWAY, _soldierPathPoints);
	soldier_4->setPosition(visibleSize / 4 + Size(0, 90));
	soldier_4->setNextDest(_soldierPathPoints->getNextPoint(soldier_4->getPosition()));
	soldier_4->setScale(1.5);
	_map->addChild(soldier_4);
	_soldiers.pushBack(soldier_4);
	_actors.pushBack(soldier_4);

	auto skillPosition = visibleSize / 4 + (Size)_map->getPosition();
	log("skillPosition: %f, %f", skillPosition.width, skillPosition.height);
	_myHero->castSkill_2(visibleSize / 4 + (Size)_map->getPosition());
}
