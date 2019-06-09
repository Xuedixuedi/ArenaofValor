#include "YaSe.h"
#include "Component/StateComponent.h"
#include "Component/Buff.h"
#include "Scene/HelloWorldScene.h"

YaSe* YaSe::create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	YaSe* yaSe = new(std::nothrow)YaSe;
	if (yaSe && yaSe->init(combatScene, camp, heroName, attackMode))
	{
		yaSe->autorelease();
		return yaSe;
	}
	CC_SAFE_DELETE(yaSe);
	return nullptr;
}

bool YaSe::init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	if (!Hero::init(combatScene, camp, heroName, attackMode))
	{
		return false;
	}

	_sprSkill = Sprite::create("pictures//hero//YaSe//YaSeSkill2Spr.png");
	auto tmp = _sprSkill;
	_sprSkill->setPosition(getBoundingBox().size / 2);
	addChild(_sprSkill);
	_sprSkill->runAction(Hide::create());

	schedule(schedule_selector(YaSe::updateHP), 2.f, -1, 0.f);

	return true;
}

bool YaSe::attack()
{
	auto nowTime = GetCurrentTime() / 1000.f;
	if (nowTime - _lastAttackTime < _minAttackInterval)
	{
		return false;
	}
	if (_vertigoLastTo > nowTime)
	{
		return false;
	}
	updateAttackTarget();
	if (!_attackTarget)
	{
		return false;
	}
	stopAllActions();
	_standingAngle = MyMath::getRad(getPosition(), _attackTarget->getPosition());
	updateDirection();
	_lastAttackTime = nowTime;
	playAttackAnimation();

	auto damage = _attack;
	if (_isEnhanced && nowTime - _lastSkillTime_1 < 3)
	{
		switch (_skillLevel_1)
		{
		case 1:
			damage += 180;
			break;
		case 2:
			damage += 230;
			break;
		case 3:
			damage += 280;
			break;
		}
	}
	_isEnhanced = false;
	Vector<Hero*>& allHeroes = _combatScene->_heroes;
	Vector<Soldier*>& allSoldiers = _combatScene->_soldiers;
	Vector<Actor*>& allTowers = _combatScene->_towers;
	for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
	{
		if ((*it)->getCamp() != _camp && !(*it)->getAlreadyDead() && getPosition().distance((*it)->getPosition()) < _attackRadius)
		{
			auto angle = MyMath::getRad(getPosition(), (*it)->getPosition());
			if (fabs(angle - _standingAngle) < 4 * MIN_DEGREE_IN_RAD)
			{
				if ((*it) == _attackTarget)
				{
					_combatScene->_damages.push_back(Damage(damage, this, *it, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
				else
				{
					_combatScene->_damages.push_back(Damage(damage * 0.5, this, *it, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
			}
		}
	}
	for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
	{
		if ((*it)->getCamp() != _camp && getPosition().distance((*it)->getPosition()) < _attackRadius)
		{
			auto angle = MyMath::getRad(getPosition(), (*it)->getPosition());
			if (fabs(angle - _standingAngle) < 4 * MIN_DEGREE_IN_RAD)
			{
				if (*it == _attackTarget)
				{
					_combatScene->_damages.push_back(Damage(damage, this, *it, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
				else
				{
					_combatScene->_damages.push_back(Damage(damage * 0.5, this, *it, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
			}
		}
	}
	for (auto it = allTowers.begin(); it != allTowers.end(); ++it)
	{
		if ((*it)->getCamp() != _camp && getPosition().distance((*it)->getPosition()) < _attackRadius + 100.f)
		{
			auto angle = MyMath::getRad(getPosition(), (*it)->getPosition());
			if (fabs(angle - _standingAngle) < 4 * MIN_DEGREE_IN_RAD)
			{
				if ((*it) == _attackTarget)
				{
					_combatScene->_damages.push_back(Damage(damage, this, *it, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
				else
				{
					_combatScene->_damages.push_back(Damage(damage * 0.5, this, *it, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
			}
		}
	}
	for (auto& i : _combatScene->_towers)
	{
		if (i->getCamp() != _camp && getPosition().distance(i->getPosition()) < _attackRadius + 100.f)
		{
			auto angle = MyMath::getRad(getPosition(), i->getPosition());
			if (fabs(angle - _standingAngle) < 4 * MIN_DEGREE_IN_RAD)
			{
				if (i == _attackTarget)
				{
					_combatScene->_damages.push_back(Damage(damage, this, i, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
				else
				{
					_combatScene->_damages.push_back(Damage(damage * 0.5, this, i, EDamageType::PHYSICS_DAMAGE, nowTime + _minAttackInterval / 2));
				}
			}
		}
	}

	return true;
}

void YaSe::updateHP(float delta)
{
	if (!_alreadyDead)
	{
		auto maxHP = _healthComp->getMaxState();
		_healthComp->changeStateBy(maxHP / 50);
	}
}

void YaSe::castSkill_1()
{
	auto nowTime = GetCurrentTime() / 1000.f;

	auto buff = Buff::create(EBuffType::NORMAL, 3.f, 0, 0, 0, 0, 0, 0, 0, _moveSpeed * 0.3, 0);
	takeBuff(buff);

	_isEnhanced = true;
}

void YaSe::castSkill_2()
{
	auto action = Sequence::create
	(
		Show::create(),
		DelayTime::create(5.f),
		Hide::create(),
		NULL
	);
	_sprSkill->runAction(action);

	schedule(schedule_selector(YaSe::applySkillDamage), 1.f, 5, 0.f);
}

void YaSe::applySkillDamage(float delta)
{
	INT32 damage;

	switch (_skillLevel_2)
	{
	case 1:
		damage = 145;
		break;
	case 2:
		damage = 181;
		break;
	case 3:
		damage = 217;
		break;
	}

	damage += _attack * 4 / 5;
	for (auto& i : _combatScene->_heroes)
	{
		if (!i->getAlreadyDead() && i->getCamp() != _camp && getPosition().distance(i->getPosition()) <= 100)
		{
			i->takeDamage(EDamageType::MAGIC_DAMAGE, damage, this);
		}
	}
	for (auto& i : _combatScene->_soldiers)
	{
		if (!i->getAlreadyDead() && i->getCamp() != _camp && getPosition().distance(i->getPosition()) <= 100)
		{
			i->takeDamage(EDamageType::MAGIC_DAMAGE, damage, this);
		}
	}
}

void YaSe::sendBuff(float delta)
{
	_attackTarget->takeBuff(Buff::create(EBuffType::VERTIGO, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

void YaSe::die()
{
	Hero::die();

	_sprSkill->runAction(Hide::create());
}

void YaSe::castSkill_3()
{
	updateAttackTarget(DEFAULT_ATTACK_RADIUS_REMOTE);
	if (_attackTarget)
	{
		auto attackHero = dynamic_cast<Soldier*>(_attackTarget);
		if (attackHero)
		{
			auto nowTime = GetCurrentTime() / 1000.f;
			_magicComp->changeStateBy(-1 * _magicConsume_3);
			_standingAngle = MyMath::getRad(getPosition(), attackHero->getPosition());
			updateDirection();
			auto delta = attackHero->getPosition() - getPosition();
			auto action = Sequence::create
			(
				MoveBy::create(0.2, delta),
				CallFunc::create(CC_CALLBACK_0(YaSe::playAttackAnimation, this)),
				NULL
			);
			runAction(action);
			if (this == _combatScene->getMyHero())
			{
				_combatScene->getMap()->runAction(MoveBy::create(0.2, -1 * delta));
			}

			auto damage = attackHero->getHealthComp()->getMaxState() * (0.1 + 0.05 * _skillLevel_3);
			_combatScene->_damages.push_back(Damage(damage, this, attackHero, EDamageType::MAGIC_DAMAGE, 0.2 + _minAttackInterval / 2));
			scheduleOnce(schedule_selector(YaSe::sendBuff), 0.2 + _minAttackInterval / 2);

			_lastAttackTime = nowTime + 0.2;
			_lastSkillTime_3 = nowTime;
		}
	}
}
