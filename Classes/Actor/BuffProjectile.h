#ifndef __BUFFPROJECTILE_H__
#define __BUFFPROJECTILE_H__

#include "cocos2d.h"
#include <string>
#include "Projectile.h"
USING_NS_CC;

class Actor;
class Buff;
class BuffProjectile :public Projectile
{
	CC_SYNTHESIZE(Buff*, _buff, Buff);

public:

	virtual bool init(Buff* buff, const std::string& filename, float damage, float speed, Actor* fromActor, Actor* target);

	static BuffProjectile* create(Buff* buff, const std::string& filename, float damage, float speed, Actor* fromActor, Actor* target);

};

#endif // !__PROJECTILE_H__