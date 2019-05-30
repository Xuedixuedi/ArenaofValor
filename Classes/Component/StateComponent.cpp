#include "StateComponent.h"



StateComponent* StateComponent::create(EStateType stateType, INT32 defaultState, INT32 defaultRecoverRate)
{
	StateComponent* StateComp = new (std::nothrow) StateComponent;
	if (StateComp && StateComp->init(stateType, defaultState, defaultRecoverRate))
	{
		StateComp->autorelease();
		return StateComp;
	}
	CC_SAFE_DELETE(StateComp);
	return nullptr;
}


bool StateComponent::init(EStateType stateType, INT32 defaultState, INT32 defaultRecoverRate)
{
	if (!LoadingBar::init())
	{
		return false;
	}

	loadTexture("slider2.png", TextureResType::LOCAL);
	_stateType = stateType;
	_maxState = defaultState;
	_currentState = defaultState;
	_recoverRate = defaultRecoverRate;
	setPercent(100);

	if (_stateType == EStateType::HEALTH)
	{
		setColor(Color3B(81, 205, 22));
	}
	else if(_stateType==EStateType::MAGIC)
	{
		setColor(Color3B(39, 123, 221));
	}

	auto background = Sprite::create("slider1.png");
	auto size = getContentSize();
	background->setPosition(size / 2);
	background->setOpacity(200);
	addChild(background,-1);
	
	_barRenderer->setZOrder(1);

	schedule(schedule_selector(StateComponent::recover), 1.f, -1, 1.f);

	return true;
}

void StateComponent::recover(float delta)
{
	if (_currentState < _maxState && _currentState>0)
	{
		changeStateBy(_recoverRate);
	}
}

void StateComponent::changeMaxBy(INT32 delta)
{
	setMaxState(_maxState + delta);
	if (delta > 0)
	{
		setCurrentState(_currentState + delta);
	}
	if (_maxState < 0)
	{
		_maxState = 0;
	}
	if (_currentState > _maxState)
	{
		_currentState = _maxState;
	}
	updatePercent();
}

void StateComponent::changeMaxTo(INT32 newMaxState)
{
	setMaxState(newMaxState);
	setCurrentState(_currentState + newMaxState - _maxState);

	updatePercent();
}

void StateComponent::changeStateBy(INT32 delta)
{
	if (_currentState < 0)
	{
		return;
	}

	_currentState += delta;

	if (_currentState > _maxState)
	{
		_currentState = _maxState;
	}
	else if (_currentState < 0)
	{
		_currentState = 0;
	}

	updatePercent();
}

void StateComponent::updatePercent()
{
	setPercent(_currentState * 100.0 / _maxState);
}

void StateComponent::changeRecoverRate(INT32 delta)
{
	_recoverRate += delta;
}