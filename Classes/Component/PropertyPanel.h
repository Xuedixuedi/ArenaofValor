#ifndef __PROPERTYPANEL_H__
#define __PROPERTYPANEL_H__

#include "cocos2d.h"
#include "Actor/Hero.h"

USING_NS_CC;


class PropertyPanel :public Sprite
{
private:

	Label* _labelLife;
	Label* _labelMagic;
	Label* _labelAttack;
	Label* _labelMoveSpeed;
	Label* _labelMagicDefense;
	Label* _labelArmor;
	Label* _labelHPRecover;
	Label* _labelMPRecover;
	Label* _labelRecords[10][5];
	size_t _heroCount;

public:

	void updatePanel(size_t playerNumber, const Vector<Hero*>& heroes);

	virtual bool init(size_t heroCount, const std::string& heroName);
	static PropertyPanel* create(size_t heroCount, const std::string& heroName);
};

#endif // !__PROPERTYPANEL_H__
