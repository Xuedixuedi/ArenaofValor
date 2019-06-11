#include "SelectHeroScene.h"
#include "SelectModeScene.h"
#include "SimpleAudioEngine.h" 
#include "Command.h"
#include "Constant.h"
#include "client.h"
USING_NS_CC;

Scene* SelectHero::createScene(chat_client* client, int PlayerNumber)
{
	auto scene = new(std::nothrow)SelectHero;
	if (scene&&scene->init(client, PlayerNumber))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectModeScene.cpp\n");
}

bool SelectHero::init(chat_client* client, int PlayerNumber)
{
	if (!Scene::init())
	{
		return false;
	}
	//netWork
	_client = client;
	_client->read_msg_list_.clear();
	_client->write_msgs_.clear();
	_playerNumber = PlayerNumber;
	_haveSelected_1 = false;
	_haveSelected_0 = false;
	_selecterHero = "";
	//声音
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("Audio/SelectYourHero.mp3", false);



	//场景
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//backmenu
	MenuItemImage *backMenu = MenuItemImage::create(
		"SelectMode/back.png",
		"SelectMode/back1.png",
		CC_CALLBACK_1(SelectHero::menuBackCallBack, this)
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
		"SelectHero/Daji.png",
		"SelectHero/Daji1.png",
		CC_CALLBACK_1(SelectHero::menuDajiCallBack, this));

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
		"SelectHero/Houyi.png",
		"SelectHero/Houyi1.png",
		CC_CALLBACK_1(SelectHero::menuHouyiCallBack, this));

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
		"SelectHero/Yase.png",
		"SelectHero/Yase1.png",
		CC_CALLBACK_1(SelectHero::menuYaseCallBack, this));


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

	auto background = Sprite::create("SelectHero/Background.png");
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


	scheduleUpdate();
	return true;
}

void SelectHero::update(float delta)
{
	if (_haveSelected_1||_haveSelected_0)
	{
		if (_haveSelected_1&&_haveSelected_0)
		{
			auto nextScene = SelectMode::create();
			Director::getInstance()->replaceScene(
				TransitionSlideInT::create(1.0f / 60, nextScene));
		}
		//发送
		Command tmpCmd;
		tmpCmd.category = 2;
		tmpCmd.player = _playerNumber;
		tmpCmd.standingAngle = 0;
		tmpCmd.isHeroMove = false;
		tmpCmd.isHeroStopMove = false;
		tmpCmd.isSkillLevelUp = false;
		tmpCmd.skillLevelUp = 0;
		tmpCmd.isGetEquip = false;
		tmpCmd.isSellEquip = false;
		tmpCmd.isCastSkill = false;
		tmpCmd.castSkill = 0;
		tmpCmd.isSkillParamter = false;
		tmpCmd.skillParamter = cocos2d::Point(1, 1);
		tmpCmd.skillParamter.x;
		tmpCmd.isAttack = false;
		tmpCmd.heroName = _selecterHero;
		//
		std::string str = tmpCmd.CreateStrings();
		chat_message msg;
		log("%s", str.c_str());
		msg.body_length(str.size());
		memcpy(msg.body(), str.c_str(), msg.body_length());
		msg.encode_header();
		_client->write(msg);
		//读取
		_client->t_lock.lock();
		if (_client->read_msg_list_.size())
		{
			std::string tmpStr = _client->read_msg_list_.front()->body();
			tmpStr.resize(_client->read_msg_list_.front()->body_length());
			Command cmd(tmpStr);
			if (cmd.category != 2)
			{
				_client->read_msg_list_.pop_front();
				_client->t_lock.unlock();
				return;
			}
			_client->read_msg_list_.pop_front();

			switch (cmd.player)
			{
			case 1:
			{
				HeroMessage newMsg = { 1,_selecterHero,ECamp::RED };
				_heroMessages.push_back(newMsg);
				_haveSelected_1 = true;
				break;
			}
			case 0:
			{
				HeroMessage newMsg = { 0,_selecterHero,ECamp::BLUE };
				_heroMessages.push_back(newMsg);
				_haveSelected_0 = true;
				break;
			}
			default:
				break;
			}
		}
		_client->t_lock.unlock(); 
	}

}


void SelectHero::menuHouyiCallBack(cocos2d::Ref * pSender)
{
	selectedHero.push("Houyi");
	_selecterHero = "HouYi";
	if (_playerNumber == 1)
	{
		if (!_haveSelected_1)
		{
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
			HeroMessage newMsg = { 1,_selecterHero,ECamp::RED };
			_heroMessages.push_back(newMsg);
		}
		_haveSelected_1 = true;
	}
	else if (_playerNumber == 0)
	{
		if (!_haveSelected_0)
		{
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
			HeroMessage newMsg = { 0,_selecterHero,ECamp::BLUE };
			_heroMessages.push_back(newMsg);
		}
		_haveSelected_0 = true;
	}
}

void SelectHero::menuDajiCallBack(cocos2d::Ref * pSender)
{
	selectedHero.push("Daji");
	_selecterHero = "DaJi";
	if (_playerNumber == 1)
	{
		if (!_haveSelected_1)
		{
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
			HeroMessage newMsg = { 1,_selecterHero,ECamp::RED };
			_heroMessages.push_back(newMsg);
		}
		_haveSelected_1 = true;
	}
	else if (_playerNumber == 0)
	{
		if (!_haveSelected_0)
		{
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
			HeroMessage newMsg = { 0,_selecterHero,ECamp::BLUE };
			//newMsg.camp = ECamp::BLUE;
			//newMsg._heroName = _selecterHero;
			//newMsg._playerNumber = _playerNumber;
			_heroMessages.push_back(newMsg);
		}
		_haveSelected_0 = true;
	}
}

void SelectHero::menuYaseCallBack(cocos2d::Ref * pSender)
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //停止播放背景音乐。
	selectedHero.push("Yase");
	_selecterHero = "YaSe";
	if (_playerNumber == 1)
	{
		if (!_haveSelected_1)
		{
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
			HeroMessage newMsg = {1,_selecterHero,ECamp::RED};
			_heroMessages.push_back(newMsg);
		}
		_haveSelected_1 = true;
	}
	else if (_playerNumber == 0)
	{
		if (!_haveSelected_0)
		{
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
			HeroMessage newMsg = { 0,_selecterHero,ECamp::BLUE };
			_heroMessages.push_back(newMsg);
		}
		_haveSelected_0 = true;
	}
}

void SelectHero::menuBackCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectMode::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

