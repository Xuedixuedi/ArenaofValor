#ifndef __SHOPLAYER_H__
#define __SHOPLAYER_H__

#include "cocos2d.h"
#include "Const/Constant.h"


USING_NS_CC;

class Buff;
class Equipment;

class ShopLayer :public Layer
{
private:

	Sprite* _sprBG;

	Sprite* _exitButton;

	Vec2 _equipLocation[NUMBER_OF_EQUIPMENT];

	Vec2 _equipGridLocation[NUMBER_OF_EQUIPGRID];

	Equipment* _equipForSell[NUMBER_OF_EQUIPMENT];

	Sprite* _ownedEquip[NUMBER_OF_EQUIPGRID];

	Vector<Buff*> _buffs;

	bool _isFilled[NUMBER_OF_EQUIPGRID];

	void initData();

public:

	Equipment* getNumberOfEquip(Point mousePosition);

	void getEquip(Equipment* equip);

	bool checkForExit(Point mousePosition);

	INT32 removeEquip(Point mousePosition);

	virtual bool init();

	CREATE_FUNC(ShopLayer);


};

#endif // !__SHOPLAYER_H__
