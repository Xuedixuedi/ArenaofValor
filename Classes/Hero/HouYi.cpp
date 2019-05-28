#include "HouYi.h"
#include "Scene/GameScene.h"


HouYi* HouYi::create(GameScene* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	HouYi* houYi = new(std::nothrow)HouYi;
	if (houYi && houYi->init(combatScene, camp, heroName, attackMode))
	{
		houYi->autorelease();
		return houYi;
	}
	CC_SAFE_DELETE(houYi);
	return nullptr;
}

bool HouYi::attack()
{
	return false;
}


bool HouYi::init(GameScene* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	if (!Hero::init(combatScene, camp, heroName, attackMode))
	{
		return false;
	}

	_skillLevel_1 = 0;
	_skillLevel_2 = 1;
	_skillLevel_3 = 0;
	_calmTime_1 = 10;
	_calmTime_2 = 0;
	_calmTime_3 = 50;
	_punishState = 0;
	_punishStateTime = 0.f;
	_lastSkillTime_1 = 0.f;
	_lastSkillTime_2 = 0.f;
	_lastSkillTime_3 = 0.f;

	return true;
}

void HouYi::skillLevelUp(INT32 skillNumber)
{
	switch (skillNumber)
	{
	case 1:
		if (_skillLevel_1 == 3)
		{
			return;
		}
		else
		{
			++_skillLevel_1;
			break;
		}
	case 2:
		if (_skillLevel_2 == 3)
		{
			return;
		}
		else
		{
			_calmTime_2 -= 2;
			++_skillLevel_2;
			break;
		}
	case 3:
		if (_skillLevel_3 == 3)
		{
			return;
		}
		else
		{
			_calmTime_3 -= 5;
			++_skillLevel_1;
			break;
		}
		break;
	}
}

void HouYi::castSkill_1()
{
	auto nowTime = GetCurrentTime() / 1000;
	//TODO: ¿ÛÀ¶
	if (_skillLevel_1 > 0 && nowTime - _lastSkillTime_1 > _calmTime_1)
	{
		takeBuff(Buff::create(EBuffType::MULTIPLE, 5, 0.5 * _attack + 100 + 100 * _skillLevel_1 * 100, 0, 0, 0, 0, 0, 0, 0, 0));
	}

	_lastSkillTime_1 = nowTime;
}

void HouYi::castSkill_2(Point mousePosition)
{
	auto nowTime = GetCurrentTime() / 1000;
	//TODO: ¿ÛÀ¶
	if (_skillLevel_2 > 0 && nowTime - _lastSkillTime_2 > _calmTime_2)
	{
		float skillRadius = 600.f;
		float effectRadius = 100.f;

		auto positionInMap = mousePosition - _combatScene->getMap()->getPosition();
		auto effectPosition = positionInMap;
		auto myPosition = getPosition();

		log("mousePosition: %f, %f", mousePosition.x, mousePosition.y);
		log("positionInMap: %f, %f", positionInMap.x, positionInMap.y);

		log("distance: %f", positionInMap.distance(myPosition));
		if (positionInMap.distance(myPosition) >= skillRadius)
		{
			log("myPosition: %f, %f", myPosition.x, myPosition.y);
			auto delta = positionInMap - myPosition;
			effectPosition = myPosition + skillRadius / delta.length() * delta;
			log("effectPosition: %f, %f", effectPosition.x, effectPosition.y);
		}

		auto skillAnimation = AnimationCache::getInstance()->getAnimation("HouYiSkill2");
		skillAnimation->setLoops(1);
		skillAnimation->setDelayPerUnit(0.07);
		auto effectSpr = Sprite::create();

		auto node = _combatScene->getMap()->getChildByTag(TAG_HOUYI_SKILL1);
		if (node)
		{
			_combatScene->getMap()->removeChild(node);
		}

		//		effectSpr->runAction(Hide::create());
		effectSpr->setPosition(effectPosition);
		effectSpr->setTag(TAG_HOUYI_SKILL1);
		_combatScene->getMap()->addChild(effectSpr);

		auto animation = Sequence::create
		(
			DelayTime::create(0.2f),
			Animate::create(skillAnimation),
			Hide::create(),
			NULL
		);
		effectSpr->runAction(animation);
		//	_combatScene->getMap()->removeChild(effectSpr);
		Vector<Hero*>& allHeroes = _combatScene->getAllHeros();
		Vector<Soldier*> allSoldiers = _combatScene->getAllSoldiers();
		auto buff = Buff::create(EBuffType::NORMAL, 2, 0, 0, 0, 0, 0, 0, 0, -180, 0);

		for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(effectPosition) <= effectRadius)
			{
				auto damage = Damage(150 + 100 * _skillLevel_2, this, *it, EDamageType::MAGIC_DAMAGE, GetCurrentTime() / 1000 + 0.5);
				_combatScene->getAllDamages().push_back(damage);

				(*it)->takeBuff(buff);
			}
		}

		for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && (*it)->getPosition().distance(effectPosition) <= effectRadius)
			{
				auto damage = Damage(150 + 100 * _skillLevel_2, this, *it, EDamageType::MAGIC_DAMAGE, GetCurrentTime() / 1000 + 0.5);
				_combatScene->getAllDamages().push_back(damage);

				(*it)->takeBuff(buff);
			}
		}
	}
	_lastSkillTime_2 = nowTime;
}

void HouYi::castSkill_3(Point point)
{



}

void HouYi::updateAttackTarget()
{
	INT32 minHealth = 10000000;
	Actor* tmpTarget = NULL;

	Vector<Hero*>& allHeroes = _combatScene->getAllHeros();
	Vector<Soldier*>& allSoldiers = _combatScene->getAllSoldiers();
	Vector<Actor*>& allTowers = _combatScene->getAllTowers();
	for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
	{
		if ((*it)->getHealthComp()->getCurrentState() < minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
		{
			minHealth = (*it)->getHealthComp()->getCurrentState();
			tmpTarget = *it;
		}
	}
	if (!tmpTarget)
	{
		for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
		{
			if ((*it)->getHealthComp()->getCurrentState() > minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
			{
				minHealth = (*it)->getHealthComp()->getCurrentState();
				tmpTarget = *it;
			}
		}
	}
	if (!tmpTarget)
	{
		for (auto it = allTowers.begin(); it != allTowers.end(); ++it)
		{
			if ((*it)->getHealthComp()->getCurrentState() > minHealth&&_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
			{
				minHealth = (*it)->getHealthComp()->getCurrentState();
				tmpTarget = *it;
			}
		}
	}
	this->setAttackTarget(tmpTarget);
}
