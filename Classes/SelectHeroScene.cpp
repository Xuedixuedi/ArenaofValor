#include "SelectHeroScene.h"
#include "SelectModeScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* SelectHeroScene::createScene()
{
	return SelectHeroScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}



bool SelectHeroScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//backmenu
	MenuItemImage *backMenu = MenuItemImage::create(
		"SelectHero/Back.png",
		"SelectHero/Back1.png",
		CC_CALLBACK_1(SelectHeroScene::menuBackCallBack, this)
	);

	if (backMenu == nullptr ||
		backMenu->getContentSize().width <= 0 ||
		backMenu->getContentSize().height <= 0)
	{
		problemLoading("'backMenu.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = visibleSize.width - 127.5;
		float y = visibleSize.height - 30;
		backMenu->setPosition(Vec2(x, y));
	}

	//OKmenu
	MenuItemImage *OKMenu = MenuItemImage::create(
		"SelectHero/OK.png",
		"SelectHero/OK1.png",
		"SelectHero/OKNO.png",
		CC_CALLBACK_1(SelectHeroScene::menuOKCallBack, this)
	);

	if (OKMenu == nullptr ||
		OKMenu->getContentSize().width <= 0 ||
		OKMenu->getContentSize().height <= 0)
	{
		problemLoading("'OKMenu.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = 1183.5;
		float y = visibleSize.height - 684.0;
		OKMenu->setPosition(Vec2(x, y));
	}

	Menu *mu = Menu::create(backMenu, OKMenu, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);

	auto background = Sprite::create("SelectHero/SelectHero.png");
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

void SelectHeroScene::menuBackCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectModeScene::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}


void SelectHeroScene::menuOKCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = HelloWorld::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}