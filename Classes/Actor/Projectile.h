#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Actor;

class Projectile :public Sprite
{
	CC_SYNTHESIZE(float, _damage, Damage);
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(Actor*, _fromActor, FromActor);
	CC_SYNTHESIZE(Actor*, _target, Target);
	
public:

	virtual bool init(const std::string& filename, float damage, float speed, Actor* fromActor, Actor* target);

	static Projectile* create(const std::string& filename, float damage, float speed, Actor* fromActor, Actor* target);

	void calculatePosition();

	float calculateDistance() const;

};

#endif // !__PROJECTILE_H__
