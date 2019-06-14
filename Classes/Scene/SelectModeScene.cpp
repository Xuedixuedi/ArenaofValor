#include "SelectModeScene.h"
#include "SelectHeroScene.h"
#include "StartGameScene.h"
#include "SimpleAudioEngine.h" 
#include "cocos2d.h"
#include "Network/Client.h"
#include "Network/Command.h"
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
	//netWork
	_doSearching = false;
	_isReady = false;
	_isGetNum = false;
	//声音
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("Audio/StartGame.mp3", true);
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。


	//backbottom
	MenuItemImage* backMenu = MenuItemImage::create(
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

	MenuItemImage* singleMenu = MenuItemImage::create(
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

	MenuItemImage* networkMenu = MenuItemImage::create(
		"pictures/SelectMode/Lianji.png",
		"pictures/SelectMode/Lianji1.png",
		CC_CALLBACK_1(SelectMode::menuNetworkCallBack, this)
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

	MenuItemImage* comingMenu = MenuItemImage::create(
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
	Menu* mu = Menu::create(backMenu, singleMenu, networkMenu, comingMenu, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);


	// add the picture splash screen"
	auto background = Sprite::create("pictures/SelectMode/background.png");
	if (background == nullptr)
	{
		problemLoading("'background.jpg'");
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

void SelectMode::update(float delta)
{
	if (_doSearching)
	{

		//稳定后确定自身编号
		if (sameTime > 30)
		{
			_playerNumber = numPlayer;
			_isGetNum = true;
		}
		if (_isGetNum)
		{
			Command tmpCmd;
			tmpCmd.category = 1;
			tmpCmd.player = _playerNumber;
			std::string str = tmpCmd.CreateStrings();
			chat_message msg;
			//TODO:test
			log("%s", str.c_str());

			//
			msg.body_length(str.size());
			memcpy(msg.body(), str.c_str(), msg.body_length());
			msg.encode_header();
			_client->write(msg);
		}
		//读取服务器的广播
		_client->t_lock.lock();
		if (_client->read_msg_list_.size())
		{
			//解析广播信息命令
			std::string tmpStr = _client->read_msg_list_.front()->body();
			tmpStr.resize(_client->read_msg_list_.front()->body_length());
			Command cmd(tmpStr);
			//如果不是连接请求，自动忽略
			if (cmd.category != 1)
			{
				//退出前解锁
				_client->read_msg_list_.pop_front();
				_client->t_lock.unlock();
				return;
			}
			//确定自身编号
			if (cmd.player >= numPlayer && !_isGetNum)
			{
				numPlayer++;
				sameTime = 0;
			}
			else if (!_isGetNum)
			{
				sameTime++;
			}
			log("%s", tmpStr.c_str());
			_client->read_msg_list_.pop_front();
			if (_isGetNum && (cmd.player == 1) || (_playerNumber == 1))
			{
				auto nextScene = SelectHero::createScene(_client, _playerNumber);
				Director::getInstance()->replaceScene(
					TransitionSlideInT::create(1.0f / 60, nextScene));
			}
		}
		else if (!_isGetNum)
		{
			sameTime++;
		}
		_client->t_lock.unlock();

	}
}

bool SelectMode::clientInit()
{
	try
	{
		sameTime = 0;
		numPlayer = 0;
		_doSearching = true;
		boost::asio::io_context* io_context = new boost::asio::io_context();
		tcp::resolver* resolver = new tcp::resolver(*io_context);
		std::string ip = "47.101.214.65";
		std::string port = "32345";
		//To test
		//ip = "192.168.31.90";
		//
		tcp::resolver::results_type* endpoints = new tcp::resolver::results_type();
		*endpoints = resolver->resolve(ip, port);
		auto c = chat_client::Create(*io_context, *endpoints);
		_client = c;

		boost::thread t(boost::bind(&boost::asio::io_context::run, io_context));
		t.detach();
	}
	catch (std::exception & e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return true;
}

void SelectMode::menuBackCallBack(Ref * pSender) {
	auto nextScene = StartGame::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menuSingleCallBack(cocos2d::Ref * pSender)
{
	auto nextScene = SelectHero::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Helo Menu Item %p", item);
}

void SelectMode::menuNetworkCallBack(cocos2d::Ref * pSender)
{
	static bool once = true;
	if (once)
	{
		clientInit();
		once = false;
	}

}

void SelectMode::menuComingCallBack(cocos2d::Ref * pSender)
{



}