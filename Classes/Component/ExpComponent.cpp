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


void ExpComponent::addExp(INT32 Exp)
{
	_currentExp += Exp;
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

	auto labelLevel = Label::create("01", "fonts/HELVETICAEXT-NORMAL.TTF", 20);
	labelLevel->setPosition(position + size / 2 - Vec2(0, 2));
	addChild(labelLevel);
	
	_level = 1;
	_currentExp = 0;
	_levelUpNeededExp = levelUpNeededExp;

	return true;
}