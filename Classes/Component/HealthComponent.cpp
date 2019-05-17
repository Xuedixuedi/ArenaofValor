#include "HealthComponent.h"



HealthComponent* HealthComponent::create(float defaultHealth, float defaultRecoverRate)
{
	HealthComponent* healthComp = new (std::nothrow) HealthComponent;
	if (healthComp && healthComp->init(defaultHealth, defaultRecoverRate))
	{
		healthComp->autorelease();
		return healthComp;
	}
	CC_SAFE_DELETE(healthComp);
	return nullptr;
}


bool HealthComponent::init(float defaultHealth, float defaultRrcoverRate)
{
	if (!LoadingBar::init())
	{
		return false;
	}

	loadTexture("slider2.png", TextureResType::LOCAL);
	setCurrentHealth(defaultHealth);
	setMaxHealth(defaultHealth);
	setRecoverRate(defaultRrcoverRate);
	setPercent(100);
	setColor(Color3B(0, 255, 55));

	auto background = Sprite::create("slider1.png");
	auto size = getContentSize();
	background->setPosition(size / 2);
	addChild(background,-1);
	
	_barRenderer->setZOrder(1);

	schedule(schedule_selector(HealthComponent::update), 1.f, -1, 0);

	return true;
}


void HealthComponent::update(float delta)
{
	if (_currentHealth < _maxHealth && _currentHealth>0)
	{
		log("Recover!");
		changeHealth(_recoverRate);
	}
}


void HealthComponent::changeMaxHealthTo(float newMaxHealth)
{
	setCurrentHealth(_currentHealth + newMaxHealth - _maxHealth);
	setMaxHealth(newMaxHealth);

	updatePercent();
}


void HealthComponent::changeHealth(float delta)
{
	if (_currentHealth < 0)
	{
		return;
	}

	_currentHealth += delta;

	if (_currentHealth > _maxHealth)
	{
		_currentHealth = _maxHealth;
	}
	else if (_currentHealth < 0)
	{
		_currentHealth = 0;
	}

	updatePercent();
}


void HealthComponent::updatePercent()
{
	setPercent(_currentHealth * 100 / _maxHealth);

	setColor(Color3B((100 - _percent) * 2.55, _percent * 2.55, _percent * 0.55));
}


void HealthComponent::changeRecoverRate(float delta)
{
	_recoverRate += delta;
}

