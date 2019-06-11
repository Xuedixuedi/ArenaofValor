#include "Equipment.h"

Equipment* Equipment::create(EEQUIPMENT equip)
{
	Equipment* equipment = new(std::nothrow)Equipment;
	if (equipment && equipment->init(equip))
	{
		equipment->autorelease();
		return equipment;
	}
	CC_SAFE_DELETE(equipment);
	return equipment;
}

bool Equipment::init(EEQUIPMENT equip)
{
	_equipName = equip;
	ValueVector equipData = FileUtils::getInstance()->getValueVectorFromFile("Data/EquipData.plist").at(static_cast<INT32>(equip)).asValueVector();
	if (!Buff::init(equipData))
	{
		return false;
	}

	setTexture(StringUtils::format("pictures/others/%d.png", static_cast<INT32>(equip) + 1));

	_goldToBuy = equipData.at(10).asInt();
	_goldForSell = equipData.at(11).asInt();
	
	return true;
}

