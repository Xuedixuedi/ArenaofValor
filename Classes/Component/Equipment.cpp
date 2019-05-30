#include "Equipment.h"

Equipment* Equipment::create(const std::string& filename, EBuffType buffType, INT32 goldToBuy, INT32 goldForSell)
{
	Equipment* equipment = new(std::nothrow)Equipment;
	if (equipment && equipment->init(filename, buffType, goldToBuy, goldForSell))
	{
		equipment->autorelease();
		return equipment;
	}
	CC_SAFE_DELETE(equipment);
	return nullptr;
}


bool Equipment::init(const std::string& filename, EBuffType buffType, INT32 goldToBuy, INT32 goldForSell)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture(filename);

	_buffType = buffType;
	_goldToBuy = goldToBuy;
	_goldForSell = goldForSell;

	return true;
}
