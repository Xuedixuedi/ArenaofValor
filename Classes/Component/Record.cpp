#include "Record.h"

bool Record::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_kill1 = 0;
	_death1 = 0;
	_assist1 = 0;
	_kill2 = 0;
	_death2 = 0;
	_assist2 = 0;
	_money = 300;

	initSprite();

	initLabel();

	schedule(schedule_selector(Record::updateMoney), 2.f, -1, 1.f);

	return true;
}

void Record::initSprite()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_sprKDA = Sprite::create("pictures/others/KDAlabel.png");
	_sprKDA->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(_sprKDA);

	//_sprKill = Sprite::create("pictures/others/Attact.png");
	//_sprKill->setPosition(Vec2(visibleSize.width * 3 / 5 + 15, visibleSize.height - 50));
	//addChild(_sprKill);

	//_sprDeath = Sprite::create("pictures/others/Dead.png");
	//_sprDeath->setPosition(Vec2(visibleSize.width * 3 / 5 + 95, visibleSize.height - 50));
	//addChild(_sprDeath);

	//_sprAssist = Sprite::create("pictures/others/Help.png");
	//_sprAssist->setPosition(Vec2(visibleSize.width * 3 / 5 + 175, visibleSize.height - 50));
	//addChild(_sprAssist);

	_sprGold = Sprite::create("pictures/others/gold.png");
	_sprGold->setPosition(Vec2(47.5, 404));
	addChild(_sprGold);
}

void Record::initLabel()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_labelKill1 = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelKill1->setColor(Color3B::WHITE);
	_labelKill1->setPosition(Vec2(337, visibleSize.height - 115.0));
	addChild(_labelKill1);

	_labelDeath1 = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelDeath1->setColor(Color3B::WHITE);
	_labelDeath1->setPosition(Vec2(402, visibleSize.height - 115.0));
	addChild(_labelDeath1);

	_labelAssist1 = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelAssist1->setColor(Color3B::WHITE);
	_labelAssist1->setPosition(Vec2(473, visibleSize.height - 115.0));
	addChild(_labelAssist1);

	_labelKill2 = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelKill2->setColor(Color3B::WHITE);
	_labelKill2->setPosition(Vec2(866, visibleSize.height - 115.0));
	addChild(_labelKill2);

	_labelDeath2 = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelDeath2->setColor(Color3B::WHITE);
	_labelDeath2->setPosition(Vec2(935, visibleSize.height - 115.0));
	addChild(_labelDeath2);

	_labelAssist2 = Label::create(StringUtils::format(" 0"), "fonts\\HELVETICAEXT-NORMAL.TTF", 14);
	_labelAssist2->setColor(Color3B::WHITE);
	_labelAssist2->setPosition(Vec2(1004, visibleSize.height - 115.0));
	addChild(_labelAssist2);

	_labelMoney = Label::create(StringUtils::format("%d", _money), "fonts\\HELVETICAEXT-NORMAL.TTF", 18);
	_labelMoney->setColor(Color3B::WHITE);
	_labelMoney->setPosition(45.5, 371);
	addChild(_labelMoney);
}

void Record::updateKill()
{
	++_kill1;
	++_death2;

	_labelKill1->setString(StringUtils::format("%2d", _kill1));
	_labelDeath2->setString(StringUtils::format("%2d", _death2));
}

void Record::updateAssist()
{
	++_assist1;
	++_death2;

	_labelAssist1->setString(StringUtils::format("%2d", _assist1));
	_labelDeath2->setString(StringUtils::format("%2d", _death2));
}

void Record::updateDeath()
{
	++_death1;
	++_kill2;

	_labelDeath1->setString(StringUtils::format("%2d", _death1));
	_labelKill2->setString(StringUtils::format("%2d", _kill2));
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
