#include "SelectHeroScene.h"
#include "SelectEnemyHeroScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;

Scene* SelectEnemyHero::createScene(const std::string& selectedHeroName)
{
	return SelectEnemyHero::create(selectedHeroName);
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}


SelectEnemyHero* SelectEnemyHero::create(const std::string& selectedHeroName)
{
	SelectEnemyHero* layerSelectEnemyHero = new(std::nothrow)SelectEnemyHero;
	if (layerSelectEnemyHero && layerSelectEnemyHero->init(selectedHeroName))
	{
		layerSelectEnemyHero->autorelease();
		return layerSelectEnemyHero;
	}
	CC_SAFE_DELETE(layerSelectEnemyHero);
	return nullptr;
}


bool SelectEnemyHero::init(const std::string& selectedHeroName)
{
	if (!Scene::init())
	{
		return false;
	}

	//声音
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Audio/SelectYourHero.mp3", false);

	_selectedHeroName = selectedHeroName;
	//场景
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//backmenu
	MenuItemImage *backMenu = MenuItemImage::create(
		"pictures/SelectMode/back.png",
		"pictures/SelectMode/back1.png",
		CC_CALLBACK_1(SelectEnemyHero::menuBackCallBack, this)
	);

	if (backMenu == nullptr ||
		backMenu->getContentSize().width <= 0 ||
		backMenu->getContentSize().height <= 0)
	{
		problemLoading("'backMenu.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + 94.5;
		float y = visibleSize.height - 30;
		backMenu->setPosition(Vec2(x, y));
	}




	//三个英雄的选择
	MenuItemImage* dajiMenu = MenuItemImage::create(
		"pictures/SelectHero/Daji.png",
		"pictures/SelectHero/Daji1.png",
		CC_CALLBACK_1(SelectEnemyHero::menuDajiCallBack, this));

	if (dajiMenu == nullptr ||
		dajiMenu->getContentSize().width <= 0 ||
		dajiMenu->getContentSize().height <= 0)
	{
		problemLoading("'daji.png' and 'daji1.png'");
	}
	else
	{
		float x = 838;
		float y = visibleSize.height - 360.5;
		dajiMenu->setPosition(Vec2(x, y));
	}

	MenuItemImage* houyiMenu = MenuItemImage::create(
		"pictures/SelectHero/Houyi.png",
		"pictures/SelectHero/Houyi1.png",
		CC_CALLBACK_1(SelectEnemyHero::menuHouyiCallBack, this));

	if (houyiMenu == nullptr ||
		houyiMenu->getContentSize().width <= 0 ||
		houyiMenu->getContentSize().height <= 0)
	{
		problemLoading("'houyi.png' and 'houyi1.png'");
	}
	else
	{
		float x = 838;
		float y = visibleSize.height - 562.5;
		houyiMenu->setPosition(Vec2(x, y));
	}

	MenuItemImage* yaseMenu = MenuItemImage::create(
		"pictures/SelectHero/Yase.png",
		"pictures/SelectHero/Yase1.png",
		CC_CALLBACK_1(SelectEnemyHero::menuYaseCallBack, this));


	if (yaseMenu == nullptr ||
		yaseMenu->getContentSize().width <= 0 ||
		yaseMenu->getContentSize().height <= 0)
	{
		problemLoading("'yase.png' and 'yase1.png'");
	}
	else
	{
		float x = 838;
		float y = visibleSize.height - 158.5;
		yaseMenu->setPosition(Vec2(x, y));
	}

	Menu *mu = Menu::create(backMenu, dajiMenu, houyiMenu, yaseMenu, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);

	auto background = Sprite::create("pictures/SelectHero/EnemyBackground.png");
	if (background == nullptr)
	{
		//problemLoading("'Timi.jpg'");
	}
	else
	{

		// position the sprite on the center of the screen
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(background, 0);
	}

	return true;
}


void SelectEnemyHero::menuHouyiCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/HouYi.wav", false, 1, 0, 1.2);
	auto nextScene = HelloWorld::create(_selectedHeroName, "HouYi");
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
}

void SelectEnemyHero::menuDajiCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/DaJi.wav", false, 1, 0, 1.2);
	auto nextScene = HelloWorld::create(_selectedHeroName, "DaJi");
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
}

void SelectEnemyHero::menuYaseCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/YaSe.wav", false, 1, 0, 1.2);
	auto nextScene = HelloWorld::create(_selectedHeroName, "YaSe");
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
}

void SelectEnemyHero::menuBackCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectHero::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

