#include "Equipment.h"

Equipment* Equipment::create(const std::string& filename, Buff* buff, INT32 goldToBuy, INT32 goldForSell)
{
	Equipment* equipment = new(std::nothrow)Equipment;
	if (equipment && equipment->init(filename, buff, goldToBuy, goldForSell))
	{
		equipment->autorelease();
		return equipment;
	}
	CC_SAFE_DELETE(equipment);
	return nullptr;
}


bool Equipment::init(const std::string& filename, Buff* buff, INT32 goldToBuy, INT32 goldForSell)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture(filename);

	_buff = buff;
	_goldToBuy = goldToBuy;
	_goldForSell = goldForSell;

	return true;
}
