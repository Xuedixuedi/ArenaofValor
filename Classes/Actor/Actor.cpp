#include "Actor.h"
#include "../Component/Bonus.h"
#include "../Component/StateComponent.h"
#include "Component/ExpComponent.h"
#include "Actor/Hero.h"
#include "Scene/HelloWorldScene.h"
#include "Actor/Projectile.h"
#include "Component/Record.h"
#include <string>

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
	//对法强的补充
	_magicAttack = 0;

	return true;
}

void Actor::takeBuff(Buff* buff)
{
	_allBuff.pushBack(buff);
	_attack += buff->getAttack();
	_defense += buff->getDefense();
	_magicDefense += buff->getMagicDefense();
	_healthComp->changeMaxBy(buff->getHP());
	_healthComp->changeRecoverRate(buff->getHPRecover());
	_minAttackInterval -= buff->getAttackInterval();
}

void Actor::clearBuff()
{
	auto nowTime = GetCurrentTime() / 1000.f;

	for (auto it = _allBuff.begin(); it != _allBuff.end();)
	{
		if ((*it)->getEndTime() <= nowTime)
		{
			removeBuff(*it);
			it = _allBuff.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Actor::takeDamage(EDamageType damageType, INT32 damage, Actor* instigator)
{
	INT32 actualDamage;

	if (damageType == EDamageType::PHYSICS_DAMAGE)
	{
		actualDamage = static_cast<INT32>((1.0 - 1.0 * _defense / (_defense + 602.f)) * damage);
	}
	else
	{
		actualDamage = static_cast<INT32>((1.0 - 1.0 * _magicDefense / (_magicDefense + 602.f)) * damage);
	}

	_healthComp->changeStateBy(-1 * actualDamage);

	_lastAttackFrom = instigator;

	if (_healthComp->getCurrentState() <= 0)
	{
		die();
	}
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

void Actor::removeBuff(Buff* buff)
{
	_attack -= buff->getAttack();
	_defense -= buff->getDefense();
	_magicDefense -= buff->getMagicDefense();
	_healthComp->changeMaxBy(-1 * buff->getHP());
	_healthComp->changeRecoverRate(-1 * buff->getHPRecover());
	_minAttackInterval += buff->getAttackInterval();
}

bool Actor::attack()
{
	auto nowTime = GetCurrentTime() / 1000.f;

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

		auto projectile = Projectile::create("pictures/others/bullet.png",  _attack, SPEED_FLY, this, _attackTarget);
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
				//log("refCount: %d", _attackTarget->getReferenceCount());
				break;
			}
		}
	}
}

void Actor::die()
{
	_alreadyDead = true;
	_allBuff.clear();

	auto lastAttackHero = dynamic_cast<Hero*>(_lastAttackFrom);
	if (lastAttackHero)
	{
		lastAttackHero->getRecordComp()->addMoney(30);
	}

	for (auto& i : _combatScene->_heroes)
	{
		if (_camp != i->getCamp())
		{
			i->getRecordComp()->addMoney(100);
			if (i->getPosition().distance(getPosition()) <= VISION_RADIUS)
			{
				i->addExp(200);
			}
		}
	}
}