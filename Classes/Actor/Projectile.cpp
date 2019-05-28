#include "Projectile.h"
#include "Actor.h"
#include "math.h"

#define PI 3.1415926

Projectile* Projectile::create(float damge, float speed, Actor* fromActor, Actor* target)
{
	Projectile* projectile = new(std::nothrow)Projectile;
	if (projectile && projectile->init(damge, speed, fromActor, target))
	{
		projectile->autorelease();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	return nullptr;
}


bool Projectile::init(float damage, float speed, Actor* fromActor, Actor* target)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture("arrow.png");
	setPosition(fromActor->getPosition());
	setScale(0.5);

	_damage = damage;
	_speed = speed;
	_fromActor = fromActor;
	_target = target;

	return true;
}


float Projectile::getAngle() const
{
	auto delta = _target->getPosition() - getPosition();
	auto dx = delta.x;
	auto dy = delta.y;

	auto angle = atan(dy / dx);
	if (angle > 0)
	{
		if (dx < 0 && dy < 0)
		{
			angle += PI;
		}
	}
	else if (angle < 0)
	{
		if (dx < 0 && dy>0)
		{
			angle += PI;
		}
	}
	angle = angle / PI * 180;


	return 360 - angle;
}

void Projectile::calculatePosition()
{
	auto delta = _target->getPosition() - getPosition();
	auto distance = delta.length();
	auto dx = delta.x;
	auto dy = delta.y;
	setRotation(getAngle());
	setPosition(getPosition() + Vec2(dx / distance * _speed / 60, dy / distance * _speed / 60));
}

float Projectile::calculateDistance() const
{
	auto delta = _target->getPosition() - getPosition();

	return delta.getLength();
}
