#ifndef __HEALTH_COMPONENT_H__
#define __HEALTH_COMPONENT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class HealthComponent :public ui::LoadingBar
{
	CC_SYNTHESIZE(float, _maxHealth, MaxHealth);
	CC_SYNTHESIZE(float, _currentHealth, CurrentHealth);
	CC_SYNTHESIZE(float, _recoverRate, RecoverRate);

public:

	void changeMaxHealthTo(float newMaxHealth);

	void changeHealth(float delta);

	void updatePercent();

	void changeRecoverRate(float delta);

	virtual bool init(float defaultHealth, float defaultRecoverRate);

	static HealthComponent* create(float defaultHealth, float defaultRecoverRate);

	virtual void update(float delta);
};


#endif
