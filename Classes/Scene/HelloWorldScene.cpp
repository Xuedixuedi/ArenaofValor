#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Component/StateComponent.h"
#include "GameController/HRocker.h"
#include "Actor/Actor.h"
#include "../Component/Record.h"
#include "Component/ExpComponent.h"
#include "Actor/Projectile.h"
#include "Actor/Hero.h"
#include "GameController/HRocker.h"

USING_NS_CC;


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
    if ( !Scene::init() )
    {
        return false;
    }
	
	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	initLabelRecord();
	initHero();
	initHRocker();
	loadingAnimation();

	scheduleUpdate();
//	test();
	

    return true;
}

void HelloWorld::initLabelRecord()
{
	_labelRecord = Record::create();
	addChild(_labelRecord);
}

void HelloWorld::initHero()
{
	_myHero = Hero::create(ECamp::BLUE, "YS", EAttackMode::MELEE);
	_myHero->setPosition(Vec2(200, 300));
	_myHero->setTag(0);
	_myHero->setScale(0.5);
	addChild(_myHero);
	_actors.pushBack(_myHero);
}

void HelloWorld::initHRocker()
{
	_rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(200, 100));
	_rocker->startRocker(true);
	addChild(_rocker);
}

void HelloWorld::loadingAnimation()
{
	String heroName = "YS";

	auto animation_00 = Animation::create();
	animation_00->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup1.png", heroName.getCString(), heroName.getCString()));
	animation_00->addSpriteFrameWithFileName(StringUtils::format("pictures\\hero\\%s\\%sup2.png", heroName.getCString(), heroName.getCString()));
	AnimationCache::getInstance()->addAnimation(animation_00,StringUtils::format("%sMoveUp",heroName.getCString()));

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
}

void HelloWorld::update(float delta)
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

	for (auto it = _actors.begin(); it !=_actors.end(); ++it)
	{
		if ((*it)->getAlreadyDead())
		{
			(*it)->setVisible(false);
		}
	}
}

void HelloWorld::updateHeroPosition()
{
	if (_rocker->getIsCanMove())
	{
		_myHero->setStandingAngle(_rocker->getAngle());
		_myHero->heroMove();
	}
	else
	{
		_myHero->stopMove();
	}
}

void HelloWorld::launch(float delta)
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

void HelloWorld::test()
{
	auto animation = AnimationCache::getInstance()->getAnimation("YSMoveDownRight");
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	auto animate = Animate::create(animation);

	_myHero->runAction(RepeatForever::create(animate));
}
