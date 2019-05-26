#include "Actor.h"
#include "../Component/Bonus.h"
#include "../Component/StateComponent.h"
#include "Component/ExpComponent.h"
#include "Actor/Hero.h"
#include "Scene/HelloWorldScene.h"
#include "Actor/Projectile.h"

Actor* Actor::create(HelloWorld* combatScene, ECamp camp)
{
	Actor* sprite = new (std::nothrow) Actor();
	if (sprite && sprite->init(combatScene, camp))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Actor::init(HelloWorld* combatScene, ECamp camp)
{
	if (camp == ECamp::RED && !Sprite::initWithFile("pictures/building/redTower.png"))
	{
		return false;
	}
	else if (camp == ECamp::BLUE && !Sprite::initWithFile("pictures/building/blueTower.png"))
	{
		return false;
	}
	
	initData(combatScene, camp);
	initHealthComp();

	return true;
}

void Actor::takeBuff(Buff* buff)
{
	_allBuff.pushBack(buff);
}

void Actor::takeDamage(EDamageType damageType, INT32 damage, Actor* instigator)
{
	if (_healthComp->getCurrentState() < damage)
	{
		_alreadyDead = true;
	}

	_healthComp->changeStateBy(-1 * damage);
	die();
}

void Actor::initData(HelloWorld* combatScene, ECamp camp)
{
	_combatScene = combatScene;
	_camp = camp;
	_defense = TOWER_ARMOR;
	_attack = TOWER_ATTACK;
	_attackRadius = TOWER_ATTACK_RADIUS;
	_alreadyDead = false;
	_magicDefense = TOWER_MAGIC_DEFNESE;
	_lastAttackTime = 0.f;
	_attackTarget = nullptr;
}

void Actor::initHealthComp()
{
	_healthComp = StateComponent::create(EStateType::HEALTH, TOWER_HP, 0);
	auto position = getPosition();
	auto size = getBoundingBox().size;
	_healthComp->setPosition(Vec2(position.x + size.width / 2, position.y + size.height));
	addChild(_healthComp);
}

bool Actor::attack()
{
	auto nowTime = GetCurrentTime() / 1000;

	if (nowTime - _lastAttackTime < TOWER_MIN_ATTACK_INTERVAL)
	{
		return false;
	}

	if (_attackTarget)
	{
		if (_attackTarget->getAlreadyDead() || _attackTarget->getPosition().distance(getPosition()) > _attackRadius)
		{
			_attackTarget = nullptr;

			updateAttackTarget();
		}
	}
	else
	{
		updateAttackTarget();
	}

	if (_attackTarget)
	{
		_lastAttackTime = nowTime;

		auto projectile = Projectile::create(_attack, SPEED_FLY, this, _attackTarget);
		projectile->setPosition(getPosition());
		projectile->setScale(2);
		_combatScene->getMap()->addChild(projectile);
		_combatScene->_bullets.pushBack(projectile);

		return true;
	}

	return false;
}

void Actor::updateAttackTarget()
{
	Vector<Hero*>& allHeroes = _combatScene->_heroes;
	for (auto& i : allHeroes)
	{
		if (!i->getAlreadyDead() && i->getCamp() != _camp && i->getPosition().distance(getPosition()) <= _attackRadius)
		{
			_attackTarget = i;
			break;
		}
	}

	if (!_attackTarget)
	{
		Vector<Soldier*>& allSoldiers = _combatScene->_soldiers;
		for (auto& i : allSoldiers)
		{
			if (!i->getAlreadyDead() && i->getCamp() != _camp && i->getPosition().distance(getPosition()) <= _attackRadius)
			{
				_attackTarget = i;
				log("refCount: %d", _attackTarget->getReferenceCount());
				break;
			}
		}
	}
}

bool Actor::die()
{
	return false;

}