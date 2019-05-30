#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include <iostream>
#include "cocos2d.h"
#include "Buff.h"

USING_NS_CC;

class Equipment :public Sprite
{
	CC_SYNTHESIZE(EBuffType, _buffType, BuffType);
	CC_SYNTHESIZE(INT32, _goldToBuy, GoldToBuy);
	CC_SYNTHESIZE(INT32, _goldForSell, GoldForSell);
	
public:

	virtual bool init(const std::string& filename, EBuffType buffType, INT32 goldToBuy, INT32 goldForSell);

	static Equipment* create(const std::string& filename, EBuffType buffType, INT32 goldToBuy, INT32 goldForSell);
};

#endif // !__EQUIPMENT_H__
