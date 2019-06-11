#include "SelectHeroScene.h"
#include "SelectModeScene.h"
#include "SimpleAudioEngine.h" 
#include "Const/Constant.h"
#include "Network/Client.h"
#include "Network/Command.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* SelectHero::createScene(chat_client* client, int PlayerNumber)
{
	auto scene = new(std::nothrow)SelectHero;
	if (scene && scene->init(client, PlayerNumber))
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
	//TODO: mutex
	//_client->write_msgs_.clear();
	_playerNumber = PlayerNumber;
	_haveSelected_1 = false;
	_haveSelected_0 = false;
	_selecterHero = "fuck";
	//声音
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Audio/SelectYourHero.mp3", false);



	//场景
	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//backmenu
	MenuItemImage* backMenu = MenuItemImage::create(
		"pictures/SelectMode/back.png",
		"pictures/SelectMode/back1.png",
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
		"pictures/SelectHero/Daji.png",
		"pictures/SelectHero/Daji1.png",
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
		"pictures/SelectHero/Houyi.png",
		"pictures/SelectHero/Houyi1.png",
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
		"pictures/SelectHero/Yase.png",
		"pictures/SelectHero/Yase1.png",
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

	Menu* mu = Menu::create(backMenu, dajiMenu, houyiMenu, yaseMenu, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);

	auto background = Sprite::create("pictures/SelectHero/Background.png");
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
	if (_haveSelected_1 || _haveSelected_0)
	{
		if (_haveSelected_1 && _haveSelected_0)
		{
			unscheduleUpdate();
			HeroMessage hmsgs;
			hmsgs.camp = ECamp::BLUE;
			hmsgs._playerNumber = 0;
			hmsgs._heroName = _map[0];
			_heroMessages.push_back(hmsgs);
			hmsgs.camp = ECamp::RED;
			hmsgs._playerNumber = 1;
			hmsgs._heroName = _map[1];
			_heroMessages.push_back(hmsgs);

			auto nextScene = HelloWorld::create(_playerNumber, _client, 1, _heroMessages);
			Director::getInstance()->replaceScene(
				TransitionSlideInT::create(1.0f / 60, nextScene));


		}
		//发送
		Command tmpCmd;
		tmpCmd.reset();
		tmpCmd.category = 2;
		tmpCmd.player = _playerNumber;
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
				_map[1] = cmd.heroName;
				_haveSelected_1 = true;
				break;
			}
			case 0:
			{
				_map[0] = cmd.heroName;
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
			_map[_playerNumber] = "HouYi";
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
		}
		_haveSelected_1 = true;
	}
	else if (_playerNumber == 0)
	{
		if (!_haveSelected_0)
		{
			_map[_playerNumber] = "HouYi";
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
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
			_map[_playerNumber] = "DaJi";
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
		}
		_haveSelected_1 = true;
	}
	else if (_playerNumber == 0)
	{
		if (!_haveSelected_0)
		{
			_map[_playerNumber] = "DaJi";
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
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
			_map[_playerNumber] = "YaSe";
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
		}
		_haveSelected_1 = true;
	}
	else if (_playerNumber == 0)
	{
		if (!_haveSelected_0)
		{
			_map[_playerNumber] = "Yase";
			_client->read_msg_list_.clear();
			_client->write_msgs_.clear();
		}
		_haveSelected_0 = true;
	}
}

void SelectHero::menuBackCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectMode::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}