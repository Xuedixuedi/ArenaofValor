#ifndef __SPRING_H__
#define __SPRING_H__

#include "cocos2d.h"
#include "Actor.h"

USING_NS_CC;

class HelloWorld;

class Spring :public Actor
{
protected:

	virtual void update(float delta);

public:

	virtual bool init(HelloWorld* combatScene, ECamp camp);

	static Spring* create(HelloWorld* combatScene, ECamp camp);

};

#endif // !__SPRING_H__
