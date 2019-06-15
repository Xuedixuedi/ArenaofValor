#include "PropertyPanel.h"
#include "Component/Record.h"
#include "Component/StateComponent.h"

PropertyPanel* PropertyPanel::create(size_t heroCount, const std::string& heroName)
{
	auto propertyPanel = new(std::nothrow)PropertyPanel;
	if (propertyPanel && propertyPanel->init(heroCount, heroName))
	{
		propertyPanel->autorelease();
		return propertyPanel;
	}
	CC_SAFE_DELETE(propertyPanel);
	return nullptr;
}

bool PropertyPanel::init(size_t heroCount, const std::string& heroName)
{
	if (!Sprite::init())
	{
		return false;
	}

	_heroCount = heroCount;
	setTexture("pictures/others/RecordBG.png");

	auto spr = Sprite::create(StringUtils::format("pictures/others/%s.png", heroName.c_str()));
	spr->setPosition(1033, 558);
	addChild(spr);

	_labelLife = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelLife->setPosition(1033, 504);
	addChild(_labelLife);

	_labelMagic = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelMagic->setPosition(1033, 449);
	addChild(_labelMagic);

	_labelAttack = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelAttack->setPosition(1033, 394);
	addChild(_labelAttack);

	_labelMoveSpeed = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelMoveSpeed->setPosition(1033, 340);
	addChild(_labelMoveSpeed);

	_labelMagicDefense = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelMagicDefense->setPosition(1033, 287);
	addChild(_labelMagicDefense);

	_labelArmor = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelArmor->setPosition(1033, 232);
	addChild(_labelArmor);

	_labelHPRecover = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelHPRecover->setPosition(1033, 177);
	addChild(_labelHPRecover);

	_labelMPRecover= Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
	_labelMPRecover->setPosition(1033, 124);
	addChild(_labelMPRecover);

	for (int i = 0; i < _heroCount; ++i)
	{
		_labelRecords[i][0] = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
		_labelRecords[i][0]->setPosition(197, 490- i * 40);
		addChild(_labelRecords[i][0]);

		_labelRecords[i][1] = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
		_labelRecords[i][1]->setPosition(335, 490 - i * 40);
		addChild(_labelRecords[i][1]);

		_labelRecords[i][2] = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
		_labelRecords[i][2]->setPosition(478, 490 - i * 40);
		addChild(_labelRecords[i][2]);

		_labelRecords[i][3] = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
		_labelRecords[i][3]->setPosition(630, 490 - i * 40);
		addChild(_labelRecords[i][3]);

		_labelRecords[i][4] = Label::create("", "HELVETICAEXT-NORMAL.TTF", 20);
		_labelRecords[i][4]->setPosition(788, 490 - i * 40);
		addChild(_labelRecords[i][4]);
	}

	return true;
}

void PropertyPanel::updatePanel(size_t playerNumber, const Vector<Hero*>& heroes)
{
	Hero* hero;
	for (int i = 0; i < _heroCount; ++i)
	{
		hero = heroes.at(i);
		_labelRecords[i][0]->setString(hero->getHeroName().getCString());
		_labelRecords[i][1]->setString(hero->getCamp() == BLUE ? "BLUE" : "RED");
		_labelRecords[i][2]->setString(StringUtils::format("%d", hero->getRecordComp()->getKill()));
		_labelRecords[i][3]->setString(StringUtils::format("%d", hero->getRecordComp()->getDeath()));
		_labelRecords[i][4]->setString(StringUtils::format("%d", hero->getRecordComp()->getAssist()));
	}

	Hero* myHero = heroes.at(playerNumber);
	_labelLife->setString(StringUtils::format("%d", myHero->getHealthComp()->getMaxState()));
	_labelMagic->setString(StringUtils::format("%d", myHero->getMagicComp()->getMaxState()));
	_labelAttack->setString(StringUtils::format("%d", myHero->getAttack()));
	_labelMoveSpeed->setString(StringUtils::format("%.0f", myHero->getMoveSpeed()));
	_labelMagicDefense->setString(StringUtils::format("%d", myHero->getMagicDefense()));
	_labelArmor->setString(StringUtils::format("%d", myHero->getDefense()));
	_labelHPRecover->setString(StringUtils::format("%d", myHero->getHealthComp()->getRecoverRate()));
	_labelMPRecover->setString(StringUtils::format("%d", myHero->getMagicComp()->getRecoverRate()));
}