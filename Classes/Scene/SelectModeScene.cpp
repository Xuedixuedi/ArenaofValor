#include "SelectModeScene.h"
#include "SelectHeroScene.h"
#include "StartGameScene.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;

Scene* SelectMode::createScene()
{
	return SelectMode::create();
}

//错误提示
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

bool SelectMode::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//声音
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//if (!audio->isBackgroundMusicPlaying()) {
	//	audio->playBackgroundMusic("Audio/StartGame.mp3", true);
	//}


	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。


	//backbottom
	MenuItemImage *backMenu = MenuItemImage::create(
		"pictures/SelectMode/back.png",
		"pictures/SelectMode/back1.png",
		CC_CALLBACK_1(SelectMode::menuBackCallBack, this)
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

	MenuItemImage *singleMenu;
	MenuItemImage *networkMenu;

	singleMenu = MenuItemImage::create(
		"pictures/SelectMode/Danji.png",
		"pictures/SelectMode/Danji1.png",
		CC_CALLBACK_1(SelectMode::menuSingleCallBack, this)
	);

	if (singleMenu == nullptr ||
		singleMenu->getContentSize().width <= 0 ||
		singleMenu->getContentSize().height <= 0)
	{
		problemLoading("'singleMenu.png'");
	}
	else
	{
		float x = origin.x + 803.0;
		float y = visibleSize.height - 182.0;
		singleMenu->setPosition(Vec2(x, y));
	}

	networkMenu = MenuItemImage::create(
		"pictures/SelectMode/Lianji.png",
		"pictures/SelectMode/Lianji1.png",
		CC_CALLBACK_1(SelectMode::menuNetworkCallBack, this, singleMenu)
	);

	if (networkMenu == nullptr ||
		networkMenu->getContentSize().width <= 0 ||
		networkMenu->getContentSize().height <= 0)
	{
		problemLoading("'networkMenu.png'");
	}
	else
	{
		float x = origin.x + 803.0;
		float y = visibleSize.height - 382.0;
		networkMenu->setPosition(Vec2(x, y));
	}

	MenuItemImage *comingMenu = MenuItemImage::create(
		"pictures/SelectMode/Qidai.png",
		"pictures/SelectMode/Qidai.png",
		CC_CALLBACK_1(SelectMode::menuComingCallBack, this)
	);

	if (comingMenu == nullptr ||
		comingMenu->getContentSize().width <= 0 ||
		comingMenu->getContentSize().height <= 0)
	{
		problemLoading("'networkMenu.png'");
	}
	else
	{
		float x = origin.x + 803.0;
		float y = visibleSize.height - 580.0;
		comingMenu->setPosition(Vec2(x, y));
	}

	//backMenu->setPosition(Director::getInstance()->convertToGL(Vec2(0, 0)));
	auto mu = Menu::create(backMenu, singleMenu, networkMenu, comingMenu, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);


	// add the picture splash screen"
	auto background = Sprite::create("pictures/SelectMode/background.png");
	if (background == nullptr)
	{
		problemLoading("'pictures/background.jpg'");
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

void SelectMode::menuBackCallBack(Ref *pSender) {
	auto nextScene = StartGame::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menuSingleCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectHero::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menuNetworkCallBack(cocos2d::Ref * pSender, MenuItemImage *tsingleMenu)
{
	if (_clickTimes) {
		return;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	auto bgSprite = Sprite::create("pictures/SelectMode/PeopleNumBack.png");
	bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	this->addChild(bgSprite, 2);

	MenuItemImage *menu5v5 = MenuItemImage::create(
		"pictures/SelectMode/5v5.png",
		"pictures/SelectMode/5v5.png",
		CC_CALLBACK_1(SelectMode::menu5v5CallBack, this)
	);

	float x = 747.0;
	float y = visibleSize.height / 2 - 200;
	menu5v5->setPosition(Vec2(x, y));

	MenuItemImage *menu1v1 = MenuItemImage::create(
		"pictures/SelectMode/1v1.png",
		"pictures/SelectMode/1v1.png",
		CC_CALLBACK_1(SelectMode::menu1v1CallBack, this)
	);

	x = 373.0;
	y = visibleSize.height / 2 - 200;
	menu1v1->setPosition(Vec2(x, y));

	auto mu = Menu::create(menu5v5, menu1v1, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 3);
	//tnetworkMenu->setEnabled(false);


	//auto nextScene = SelectHero::create();
	//Director::getInstance()->replaceScene(
	//	TransitionSlideInT::create(1.0f / 60, nextScene));
	//MenuItem *item = (MenuItem*)pSender;
	//log("Touch Helo Menu Item %p", item);

	_clickTimes++;

}

void SelectMode::menu5v5CallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectHero::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menu1v1CallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectHero::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menuComingCallBack(cocos2d::Ref * pSender)
{
}

