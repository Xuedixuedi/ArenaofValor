#include "ExpComponent.h"

ExpComponent* ExpComponent::create(INT32 levelUpNeededExp)
{
	ExpComponent* expComp = new (std::nothrow) ExpComponent;
	if (expComp && expComp->init(levelUpNeededExp))
	{
		expComp->autorelease();
		return expComp;
	}
	CC_SAFE_DELETE(expComp);
	return nullptr;
}

bool ExpComponent::init(INT32 levelUpNeededExp)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture("rocker.png");

	auto position = getPosition();
	auto size = getContentSize();

	_labelLevel = Label::create("1", "fonts/HELVETICAEXT-NORMAL.TTF", 20);
	_labelLevel->setPosition(position + size / 2 - Vec2(0, 2));
	addChild(_labelLevel);
	
	_level = 1;
	_currentExp = 0;
	_levelUpNeededExp = levelUpNeededExp;

	return true;
}

bool ExpComponent::addExp(INT32 Exp)
{
	_currentExp += Exp;

	if (_currentExp >= _levelUpNeededExp)
	{
		++_level;
		_labelLevel->setString(StringUtils::format("%d", _level));

		_currentExp -= _levelUpNeededExp;

		return true;
	}

	return false;
}