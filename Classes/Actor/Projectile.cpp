#include "Projectile.h"
#include "Actor.h"
#include "math.h"

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
	auto angle = MyMath::getRad(getPosition(), _target->getPosition());
	setRotation(360 - angle / M_PI * 180);
	setPosition(getPosition() + MyMath::calculatePositionDelta(angle, SPEED_FLY));
}

float Projectile::calculateDistance() const
{
	auto delta = _target->getPosition() - getPosition();

	return delta.getLength();
}
