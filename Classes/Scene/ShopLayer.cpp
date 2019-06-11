#include "ShopLayer.h"
#include "Component/Buff.h"
#include "Component/Equipment.h"

bool ShopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_sprBG = Sprite::create("pictures//others//ShopLayer.png");
	addChild(_sprBG);

	initData();

	return true;
}

void ShopLayer::initData()
{
	auto buff_0 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, 300, 0);
	_buffs.pushBack(buff_0);
	_equipForSell[0] = Equipment::create("pictures//others//1.png", buff_0, 250, 150);
	_equipLocation[0] = Vec2(269, 575);
	_equipForSell[0]->setPosition(_equipLocation[0]);
	_sprBG->addChild(_equipForSell[0]);

	auto buff_1 = Buff::create(EBuffType::NORMAL,0, 20, 0, 0, 0, 0, 0, 0, 0, 0);
	_buffs.pushBack(buff_1);
	_equipForSell[1] = Equipment::create("pictures//others//2.png", buff_1, 250, 150);
	_equipLocation[1] = Vec2(269, 468);
	_equipForSell[1]->setPosition(_equipLocation[1]);
	_sprBG->addChild(_equipForSell[1]);

	auto buff_2 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.15);
	_buffs.pushBack(buff_2);
	_equipForSell[2] = Equipment::create("pictures//others//3.png", buff_2, 290, 174);
	_equipLocation[2] = Vec2(504, 468);
	_equipForSell[2]->setPosition(_equipLocation[2]);
	_sprBG->addChild(_equipForSell[2]);

	auto buff_3 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 0, 0, 300, 0, 0, 0, 0);
	_buffs.pushBack(buff_3);
	_equipForSell[3] = Equipment::create("pictures//others//4.png", buff_3, 220, 130);
	_equipLocation[3] = Vec2(269, 360);
	_equipForSell[3]->setPosition(_equipLocation[3]);
	_sprBG->addChild(_equipForSell[3]);

	auto buff_4 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0);
	_buffs.pushBack(buff_4);
	_equipForSell[4] = Equipment::create("pictures//others//5.png", buff_4, 120, 72);
	_equipLocation[4] = Vec2(504, 360);
	_equipForSell[4]->setPosition(_equipLocation[4]);
	_sprBG->addChild(_equipForSell[4]);

	auto buff_5 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 0, 300, 0, 0, 0, 0, 0);
	_buffs.pushBack(buff_5);
	_equipForSell[5] = Equipment::create("pictures//others//6.png", buff_5, 300, 180);
	_equipLocation[5] = Vec2(269, 254);
	_equipForSell[5]->setPosition(_equipLocation[5]);
	_sprBG->addChild(_equipForSell[5]);

	auto buff_6 = Buff::create(EBuffType::NORMAL, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0);
	_buffs.pushBack(buff_6);
	_equipForSell[6] = Equipment::create("pictures//others//7.png", buff_6, 220, 132);
	_equipLocation[6] = Vec2(504, 254);
	_equipForSell[6]->setPosition(_equipLocation[6]);
	_sprBG->addChild(_equipForSell[6]);

	auto buff_7 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 90, 0, 0, 0, 0, 0, 0);
	_buffs.pushBack(buff_7);
	_equipForSell[7] = Equipment::create("pictures//others//8.png", buff_7, 220, 132);
	_equipLocation[7] = Vec2(739, 254);
	_equipForSell[7]->setPosition(_equipLocation[7]);
	_sprBG->addChild(_equipForSell[7]);

	auto buff_8 = Buff::create(EBuffType::NORMAL, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0);
	_buffs.pushBack(buff_8);
	_equipForSell[8] = Equipment::create("pictures//others//9.png", buff_8, 140, 84);
	_equipLocation[8] = Vec2(974, 254);
	_equipForSell[8]->setPosition(_equipLocation[8]);
	_sprBG->addChild(_equipForSell[8]);

	for (int i = 0; i < NUMBER_OF_EQUIPGRID; ++i)
	{
		_ownedEquip[i] = Sprite::create();
		_ownedEquip[i]->setPosition(Vec2(381 + 115 * i, 140));
		_sprBG->addChild(_ownedEquip[i]);
		_isFilled[i] = false;
		_equipGridLocation[i] = Vec2(381 + i * 115, 140);
	}

	_exitButton = Sprite::create("pictures//others//ExitButton.png");
	_exitButton->setPosition(Vec2(1112, 620));
	_sprBG->addChild(_exitButton);
}

Equipment* ShopLayer::getNumberOfEquip(Point mousePosition)
{
	INT32 res = -1;

	for (int i = 0; i < NUMBER_OF_EQUIPMENT; ++i)
	{
		if (mousePosition.distance(_equipLocation[i]) < EQUIP_CIRCLE_RADIUS)
		{
			res = i;
			break;
		}
	}
	if (res == -1)
	{
		return nullptr;
	}

	for (int i = 0; i < NUMBER_OF_EQUIPGRID; ++i)
	{
		if (!_isFilled[i])
		{
			auto buff = _equipForSell[res]->getBuff();
			log("%d", buff->getAttack());
			log("%f", _equipForSell[res]->getBuff()->getMoveSpeed());
			return _equipForSell[res];
		}
	}

	return nullptr;
}

void ShopLayer::getEquip(Equipment* equip)
{
	INT32 equipNumber;
	for (int i = 0; i < NUMBER_OF_EQUIPMENT; ++i)
	{
		if (equip == _equipForSell[i])
		{
			equipNumber = i;
			break;
		}
	}
	for (int i = 0; i < NUMBER_OF_EQUIPGRID; ++i)
	{
		if (!_isFilled[i])
		{
			_ownedEquip[i]->setTexture(StringUtils::format("pictures//others//%d.png", equipNumber + 1));
			_ownedEquip[i]->setVisible(true);
			_isFilled[i] = true;
			return;
		}
	}
}

bool ShopLayer::checkForExit(Point mousePosition)
{
	return _exitButton->getBoundingBox().containsPoint(mousePosition);
}

INT32 ShopLayer::removeEquip(Point mousePosition)
{
	for (int i = 0; i < NUMBER_OF_EQUIPGRID; ++i)
	{
		if (_isFilled[i] && _equipGridLocation[i].distance(mousePosition) < EQUIP_CIRCLE_RADIUS)
		{
			_ownedEquip[i]->setVisible(false);
			_isFilled[i] = false;
			return i;
		}
	}

	return -1;
}
