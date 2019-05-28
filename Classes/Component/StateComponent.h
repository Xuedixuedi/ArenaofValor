#ifndef __HEALTH_COMPONENT_H__
#define __HEALTH_COMPONENT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

enum EStateType
{
	HEALTH,
	MAGIC
};

class StateComponent :public ui::LoadingBar
{
	CC_SYNTHESIZE(EStateType, _stateType, StateType);
	//生命值上限
	CC_SYNTHESIZE(INT32, _maxState, MaxState);
	//当前生命值
	CC_SYNTHESIZE(INT32, _currentState, CurrentState);

	CC_SYNTHESIZE(INT32, _recoverRate, RecoverRate);

public:

	void changeMaxBy(INT32 delta);

	void changeMaxTo(INT32 newMaxState);

	void changeStateBy(INT32 delta);

	void updatePercent();

	virtual void recover(float delta);

	void changeRecoverRate(INT32 delta);

	virtual bool init(EStateType stateType, INT32 defaultState, INT32 defaultRecoverRate);

	static StateComponent* create(EStateType stateType, INT32 defaultState, INT32 defaultRecoverRate);

};


#endif