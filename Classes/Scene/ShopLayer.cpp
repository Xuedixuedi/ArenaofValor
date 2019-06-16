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
	_equipForSell[0] = Equipment::create(EEQUIPMENT::CAOXIE);
	_equipLocation[0] = Vec2(269, 575);
	_equipForSell[0]->setPosition(_equipLocation[0]);
	_sprBG->addChild(_equipForSell[0]);

	_equipForSell[1] = Equipment::create(EEQUIPMENT::TIEJIAN);
	_equipLocation[1] = Vec2(269, 468);
	_equipForSell[1]->setPosition(_equipLocation[1]);
	_sprBG->addChild(_equipForSell[1]);

	_equipForSell[2] = Equipment::create(EEQUIPMENT::BISHOU);
	_equipLocation[2] = Vec2(504, 468);
	_equipForSell[2]->setPosition(_equipLocation[2]);
	_sprBG->addChild(_equipForSell[2]);

	_equipForSell[3] = Equipment::create(EEQUIPMENT::LANBAOSHI);
	_equipLocation[3] = Vec2(269, 360);
	_equipForSell[3]->setPosition(_equipLocation[3]);
	_sprBG->addChild(_equipForSell[3]);

	_equipForSell[4] = Equipment::create(EEQUIPMENT::HUFU);
	_equipLocation[4] = Vec2(504, 360);
	_equipForSell[4]->setPosition(_equipLocation[4]);
	_sprBG->addChild(_equipForSell[4]);

	_equipForSell[5] = Equipment::create(EEQUIPMENT::HONGBAOSHI);
	_equipLocation[5] = Vec2(269, 254);
	_equipForSell[5]->setPosition(_equipLocation[5]);
	_sprBG->addChild(_equipForSell[5]);

	_equipForSell[6] = Equipment::create(EEQUIPMENT::PIFENG);
	_equipLocation[6] = Vec2(504, 254);
	_equipForSell[6]->setPosition(_equipLocation[6]);
	_sprBG->addChild(_equipForSell[6]);

	_equipForSell[7] = Equipment::create(EEQUIPMENT::BUJIA);
	_equipLocation[7] = Vec2(739, 254);
	_equipForSell[7]->setPosition(_equipLocation[7]);
	_sprBG->addChild(_equipForSell[7]);

	_equipForSell[8] = Equipment::create(EEQUIPMENT::SHUIJIN);
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

Equipment* ShopLayer::getEquipByEnum(EEQUIPMENT equipName)
{
	for (int i = 0; i < NUMBER_OF_EQUIPMENT; ++i)
	{
		if (_equipForSell[i]->getEquipName() == equipName)
		{
			return _equipForSell[i];
		}
	}
}
