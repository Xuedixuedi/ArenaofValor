#include "BuffProjectile.h"
#include "Projectile.h"
#include "Actor.h"
#include "math.h"

BuffProjectile * BuffProjectile::create(Buff * buff, const std::string & filename, float damage, float speed, Actor * fromActor, Actor * target)
{
	BuffProjectile* buffProjectile = new(std::nothrow)BuffProjectile;
	if (buffProjectile&&buffProjectile->init(buff, filename, damage, speed, fromActor, target))
	{
		buffProjectile->autorelease();
		return buffProjectile;
	}
	CC_SAFE_DELETE(buffProjectile);
	return nullptr;
}


bool BuffProjectile::init(Buff * buff, const std::string & filename, float damage, float speed, Actor * fromActor, Actor * target)
{
	if (!Projectile::init(filename, damage, speed, fromActor, target))
	{
		return false;
	}

	_buff = buff;

	return true;
}

