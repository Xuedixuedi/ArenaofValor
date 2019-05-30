#include "Record.h"

bool Record::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_kill = 0;
	_death = 0;
	_assist = 0;
	_money = 300;

	initSprite();

	initLabel();


	schedule(schedule_selector(Record::updateMoney), 1.f, -1, 1.f);

	return true;
}

void Record::initSprite()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto sprKill = Sprite::create("pictures/others/Attact.png");
	sprKill->setPosition(Vec2(visibleSize.width * 3 / 5 + 15, visibleSize.height - 50));
	addChild(sprKill);

	auto sprDeath = Sprite::create("pictures/others/Dead.png");
	sprDeath->setPosition(Vec2(visibleSize.width * 3 / 5 + 95, visibleSize.height - 50));
	addChild(sprDeath);

	auto sprAssist = Sprite::create("pictures/others/Help.png");
	sprAssist->setPosition(Vec2(visibleSize.width * 3 / 5 + 175, visibleSize.height - 50));
	addChild(sprAssist);

	auto sprGold = Sprite::create("pictures/others/gold.png");
	auto boundingBoxSize = sprGold->getBoundingBox().size;
	sprGold->setPosition(Vec2(47.5, 404));
	addChild(sprGold);
}

void Record::initLabel()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_labelKill = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelKill->setColor(Color3B::WHITE);
	_labelKill->setPosition(Vec2(visibleSize.width * 3 / 5 + 40, visibleSize.height - 50));
	addChild(_labelKill);

	_labelDeath = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelDeath->setColor(Color3B::WHITE);
	_labelDeath->setPosition(Vec2(visibleSize.width * 3 / 5 + 120, visibleSize.height - 50));
	addChild(_labelDeath);

	_labelAssist = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelAssist->setColor(Color3B::WHITE);
	_labelAssist->setPosition(Vec2(visibleSize.width * 3 / 5 + 200, visibleSize.height - 50));
	addChild(_labelAssist);

	_labelMoney = Label::create(StringUtils::format("%d", _money), "fonts\\HELVETICAEXT-NORMAL.TTF", 18);
	_labelMoney->setColor(Color3B::WHITE);
	_labelMoney->setPosition(45.5, 371);
	addChild(_labelMoney);
}

void Record::updateKill()
{
	++_kill;
	
	_labelKill->setString(StringUtils::format("%2d", _kill));
}

void Record::updateAssist()
{
	++_assist;

	_labelAssist->setString(StringUtils::format("%2d", _assist));
}

void Record::updateDeath()
{
	++_death;

	_labelDeath->setString(StringUtils::format("%2d", _death));
}

void Record::updateMoney(float delta)
{
	++_money;

	_labelMoney->setString(StringUtils::format("%4d", _money));
}

void Record::addMoney(INT32 delta)
{
	_money += delta;

	_labelMoney->setString(StringUtils::format("%4d", _money));
}
