#pragma once

#ifndef __AIHERO_H__
#define __AIHERO_H__

#include "cocos2d.h"
#include "Actor/Hero.h"

USING_NS_CC;

class SoldierPath;

class AIHero :public Hero
{
	CC_SYNTHESIZE(Actor*, _instigator, Instigator);
	CC_SYNTHESIZE(Vec2, _nextDest, NextDest);
	CC_SYNTHESIZE(bool, _isMovingToDest, IsMovingToDest);

protected:

	SoldierPath* _pathPoints;

	void startAnimation();

	void moveTo(const Vec2& targetPosition);

	virtual bool attack() override;

	bool updateInstigator();

public:

	void updateState();

	virtual bool init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode, SoldierPath* pathPoints);

	static AIHero* create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode, SoldierPath* pathPoints);
};

#endif // !__AIHERO_H__
