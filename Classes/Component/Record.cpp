#include "Record.h"

bool Record::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initSprite();

	initLabel();

	_kill = 0;
	_death = 0;
	_assist = 0;

	return true;
}

void Record::initSprite()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto sprKill = Sprite::create("pictures\\others\\Attact.png");
	sprKill->setPosition(Vec2(visibleSize.width * 3 / 5 + 15, visibleSize.height - 50));
	addChild(sprKill);

	auto sprDeath = Sprite::create("pictures\\others\\Dead.png");
	sprDeath->setPosition(Vec2(visibleSize.width * 3 / 5 + 95, visibleSize.height - 50));
	addChild(sprDeath);

	auto sprAssist = Sprite::create("pictures\\others\\Help.png");
	sprAssist->setPosition(Vec2(visibleSize.width * 3 / 5 + 175, visibleSize.height - 50));
	addChild(sprAssist);
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
