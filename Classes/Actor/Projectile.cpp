#include "Projectile.h"
#include "Actor.h"
#include "math.h"

#define PI 3.1415926

Projectile* Projectile::create(const std::string& filename, float damge, float speed, Actor* fromActor, Actor* target)
{
	Projectile* projectile = new(std::nothrow)Projectile;
	if (projectile && projectile->init(filename, damge, speed, fromActor, target))
	{
		projectile->autorelease();
		return projectile;
	}
	CC_SAFE_DELETE(projectile);
	return nullptr;
}


bool Projectile::init(const std::string& filename, float damage, float speed, Actor* fromActor, Actor* target)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture(filename);
	setPosition(fromActor->getPosition());
	setScale(0.5);

	_damage = damage;
	_speed = speed;
	_fromActor = fromActor;
	_target = target;

	return true;
}

void Projectile::calculatePosition()
{
	auto delta = _target->getPosition() - getPosition();
	auto distance = delta.length();
	auto dx = delta.x;
	auto dy = delta.y;
	setRotation(360 - MyMath::getRad(getPosition(), _target->getPosition()) / M_PI * 180);
	setPosition(getPosition() + Vec2(dx / distance * _speed / 60, dy / distance * _speed / 60));
}

float Projectile::calculateDistance() const
{
	auto delta = _target->getPosition() - getPosition();

	return delta.getLength();
}
