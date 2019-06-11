#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include <iostream>
#include "cocos2d.h"
#include "Buff.h"
#include "Const/Constant.h"

USING_NS_CC;

class Equipment :public Buff
{
	CC_SYNTHESIZE(INT32, _goldToBuy, GoldToBuy);
	CC_SYNTHESIZE(INT32, _goldForSell, GoldForSell);
	CC_SYNTHESIZE(EEQUIPMENT, _equipName, EquipName);
	
public:

	virtual bool init(EEQUIPMENT equip);

	static Equipment* create(EEQUIPMENT equip);
};

#endif // !__EQUIPMENT_H__
