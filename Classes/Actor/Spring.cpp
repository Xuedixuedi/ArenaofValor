#include "Spring.h"
#include "Scene/HelloWorldScene.h"

Spring* Spring::create(HelloWorld* combatScene, ECamp camp)
{
	auto spring = new(std::nothrow)Spring;
	if (spring && spring->init(combatScene, camp))
	{
		spring->autorelease();
		return spring;
	}
	CC_SAFE_DELETE(spring);
	return nullptr;
}


bool Spring::init(HelloWorld* combatScene, ECamp camp)
{
	if (!Actor::init("pictures/building/redTower.png", combatScene, camp))
	{
		return false;
	}

	if (camp == ECamp::BLUE)
	{
		setTexture("pictures//others//BlueSpring.png");
	}
	else
	{
		setTexture("pictures//others//RedSpring.png");
	}
	_minAttackInterval = 0.15;
	_healthComp->setVisible(false);

	_attackRadius = 400;

	scheduleUpdate();

	return true;
}

void Spring::update(float delta)
{
	attack();

	for (auto& i : _combatScene->_heroes)
	{
		if (getPosition().distance(i->getPosition()) < _attackRadius && !i->getAlreadyDead() && _camp == i->getCamp())
		{
			i->getHealthComp()->changeStateBy(15);
			i->getMagicComp()->changeStateBy(10);
		}
	}
	
	for (auto& i : _combatScene->_soldiers)
	{
		if (getPosition().distance(i->getPosition()) < _attackRadius && _camp == i->getCamp())
		{
			i->getHealthComp()->changeStateBy(15);
		}
	}
}
