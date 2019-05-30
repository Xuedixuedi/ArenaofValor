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

	schedule(schedule_selector(YaSe::updateHP), 2.f, -1, 0.f);

	return true;
}

bool YaSe::attack()
{
	return false;
}

void YaSe::updateHP(float delta)
{
	auto maxHP = _healthComp->getMaxState();
	_healthComp->changeStateBy(maxHP / 50);
}

void YaSe::castSkill_1()
{
	auto nowTime = GetCurrentTime() / 1000.f;

	if (_lastSkillTime_1 + _calmTime_1 >= nowTime && _silenceLastTo > nowTime)
	{
		return;
	}

	auto buff = Buff::create(EBuffType::NORMAL, 3.f, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	takeBuff(buff);

	_isEnhanced = true;
}

void YaSe::castSkill_2()
{
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

void YaSe::castSkill_3()
{

}
