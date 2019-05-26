#include "SelectModeScene.h"
#include "SelectHeroScene.h"
#include "StartGameScene.h"

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

	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。


	//backbottom
	MenuItemImage *backMenu = MenuItemImage::create(
		"SelectMode/back.png",
		"SelectMode/back1.png",
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

	MenuItemImage *onevoneMenu = MenuItemImage::create(
		"SelectMode/1v1.png",
		"SelectMode/1v11.png",
		CC_CALLBACK_1(SelectMode::menu1v1CallBack, this)
	);

	if (onevoneMenu == nullptr ||
		onevoneMenu->getContentSize().width <= 0 ||
		onevoneMenu->getContentSize().height <= 0)
	{
		problemLoading("'1v1.png' and '1v1.png'");
	}
	else
	{
		float x = origin.x + 783.5;
		float y = visibleSize.height - 387.5;
		onevoneMenu->setPosition(Vec2(x, y));
	}

	//backMenu->setPosition(Director::getInstance()->convertToGL(Vec2(0, 0)));
	Menu *mu = Menu::create(backMenu, onevoneMenu, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);


	// add the picture splash screen"
	auto background = Sprite::create("SelectMode/PVE1.png");
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

void SelectMode::menuBackCallBack(Ref *pSender) {
	auto nextScene = StartGame::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menu1v1CallBack(Ref *pSender) {
	auto nextScene = SelectHero::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}