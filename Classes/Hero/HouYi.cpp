#include "HouYi.h"
#include "Scene/HelloWorldScene.h"


HouYi* HouYi::create(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
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

bool HouYi::init(HelloWorld* combatScene, ECamp camp, std::string heroName, EAttackMode attackMode)
{
	if (!Hero::init(combatScene, camp, heroName, attackMode))
	{
		return false;
	}

	_punishState = 0;
	_punishStateTime = 0.f;

	return true;
}

void HouYi::castSkill_1()
{
	
	auto nowTime = GetCurrentTime() / 1000.f;
	if (_multipleLastTo >= nowTime)
	{
		return;
	}
	//TODO: 扣蓝
	if (_skillLevel_1 > 0 && nowTime - _lastSkillTime_1 > _calmTime_1)
	{
		takeBuff(Buff::create(EBuffType::MULTIPLE, 5, 0.5 * _attack + 100 + _skillLevel_1 * 100, 0, 0, 0, 0, 0, 0, 0, 0));

	}

	_lastSkillTime_1 = nowTime;

	
	//For test
	attack();
}

void HouYi::castSkill_2(Point mousePosition)
{
	//For test
	_calmTime_2 = 0.01;
	//
	auto nowTime = GetCurrentTime() / 1000.f;
	//TODO: 扣蓝
	_magicComp->changeStateBy(-1 * _magicConsume_2);
	if (_skillLevel_2 > 0 && nowTime - _lastSkillTime_2 > _calmTime_2)
	{
		float skillRadius = 500.f;
		float effectRadius = 150.f;

		auto positionInMap = mousePosition - _combatScene->getMap()->getPosition();
		auto effectPosition = positionInMap;
		auto myPosition = getPosition();

		if (positionInMap.distance(myPosition) >= skillRadius)
		{
			auto delta = positionInMap - myPosition;
			effectPosition = myPosition + skillRadius / delta.length() * delta;
		}
		//转身
		_standingAngle = MyMath::getRad(getPosition(), mousePosition);
		updateDirection();
		//
		auto skillAnimation = AnimationCache::getInstance()->getAnimation("HouYiSkill2");
		skillAnimation->setLoops(1);
		skillAnimation->setDelayPerUnit(0.07);
		auto effectSpr = Sprite::create();

		auto node = _combatScene->getMap()->getChildByTag(TAG_HOUYI_SKILL2);
		if (node)
		{
			_combatScene->getMap()->removeChild(node);
		}

		//		effectSpr->runAction(Hide::create());
		effectSpr->setPosition(effectPosition);
		effectSpr->setTag(TAG_HOUYI_SKILL2);
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

		Vector<Hero*>& allHeroes = _combatScene->_heroes;
		Vector<Soldier*> allSoldiers = _combatScene->_soldiers;
		auto buff = Buff::create(EBuffType::NORMAL, 2, 0, 0, 0, 0, 0, 0, 0, -180, 0);

		for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(effectPosition) <= effectRadius)
			{
				auto damage = Damage(150 + 100 * _skillLevel_2, this, *it, EDamageType::MAGIC_DAMAGE, GetCurrentTime() / 1000 + 0.5);
				_combatScene->_damages.push_back(damage);

				(*it)->takeBuff(buff);
			}
		}

		for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && (*it)->getPosition().distance(effectPosition) <= effectRadius)
			{
				auto damage = Damage(150 + 100 * _skillLevel_2, this, *it, EDamageType::MAGIC_DAMAGE, GetCurrentTime() / 1000 + 0.5);
				_combatScene->_damages.push_back(damage);

				(*it)->takeBuff(buff);
			}
		}
		_lastSkillTime_2 = nowTime;
	}

}

void HouYi::castSkill_3(Point mousePosition)
{
	_magicComp->changeStateBy(-1 * _magicConsume_3);
	auto nowTime = GetCurrentTime() / 1000.f;
	_lastSkillTime_3 = nowTime;
	_birdAngle = MyMath::getRad(getPosition(), mousePosition - _combatScene->getMap()->getPosition());
	_skillPosition = getPosition();

	auto sprSkill = Sprite::create("pictures//others//YaSeleft.png");
	sprSkill->setPosition(getPosition());
	sprSkill->setTag(TAG_HOUYI_SKILL3);
	_combatScene->getMap()->addChild(sprSkill);

	schedule(schedule_selector(HouYi::updateSprSkillPosition), 1 / 60, -1, 0.f);
}

void HouYi::updateSprSkillPosition(float delta)
{
	float effectRadius = 100.f;
	auto sprSkill = dynamic_cast<Sprite*>(_combatScene->getMap()->getChildByTag(TAG_HOUYI_SKILL3));
	auto deltaPosition = MyMath::calculatePositionDelta(_birdAngle, SPEED_FLY);
	auto newPosition = sprSkill->getPosition() + deltaPosition;
	sprSkill->setPosition(newPosition);
	float contactLimit = 20.f + sprSkill->getBoundingBox().size.width / 2;

	if (sprSkill->getPosition().distance(_skillPosition) > 2000.f)
	{
		unschedule(schedule_selector(HouYi::updateSprSkillPosition));
		_combatScene->getMap()->removeChild(sprSkill);
		return;
	}

	auto targetPosition = Vec2::ZERO;
	for (auto it = _combatScene->_soldiers.begin(); it != _combatScene->_soldiers.end(); ++it)
	{
		if (_camp != (*it)->getCamp() && (*it)->getPosition().distance(sprSkill->getPosition()) < contactLimit)
		{
			unschedule(schedule_selector(HouYi::updateSprSkillPosition));
			_combatScene->getMap()->removeChild(sprSkill);
			targetPosition = (*it)->getPosition();
			break;
		}
	}

	if (targetPosition != Vec2::ZERO)
	{
		auto buff = Buff::create(EBuffType::VERTIGO, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		auto damage = 525 + _skillLevel_3 * 175;
		for (auto it = _combatScene->_soldiers.begin(); it != _combatScene->_soldiers.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && (*it)->getPosition().distance(targetPosition) < effectRadius)
			{
				(*it)->takeBuff(buff);
				(*it)->takeDamage(EDamageType::MAGIC_DAMAGE, damage, this);
			}
		}
	}
}


bool HouYi::attack()
{
	auto nowTime = GetCurrentTime() / 1000.f;
	//当不满足攻击间隔的时候，按攻击键调attack的情况
	if (_isAttacking&&nowTime - _lastAttackTime < _minAttackInterval)
	{
		return false;
	}
	//先重新生成攻击目标
	updateAttackTarget();
	if (!_attackTarget)
	{
		auto animation = Animation::create();
		animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%sAttackRight", _heroName.getCString()));
		animation->setDelayPerUnit(_minAttackInterval * 10);
		animation->setLoops(1);
		auto animate = Animate::create(animation);
		runAction(animate);
		return false;
	}
	//更新攻击状态和停止动画
	stopAllActions();
	_isAttacking = true;
	//根据新的攻击目标计算攻击时人物的角度
	_standingAngle = MyMath::getRad(getPosition(), _attackTarget->getPosition());
	updateDirection();
	//播放攻击动画
	playAttackAnimation();

	if (_punishState < 3)
	{
		auto projectile = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack, SPEED_FLY, this, _attackTarget);
		projectile->setScale(1.5f);
		_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 3, projectile);
	}
	else
	{
		auto projectile1 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.5, SPEED_FLY, this, _attackTarget);
		auto projectile2 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.5, SPEED_FLY*0.7, this, _attackTarget);
		auto projectile3 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.5, SPEED_FLY*0.4, this, _attackTarget);
		projectile1->setScale(1.5f);
		projectile2->setScale(1.5f);
		projectile3->setScale(1.5f);
		_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 3, projectile1);
		_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 6, projectile2);
		_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 9, projectile3);
	}
	//考虑多重箭的buff效果
	if (_multipleLastTo >= nowTime)
	{
		Actor* attackTarget2 = NULL;
		Actor* attackTarget3 = NULL;
		Vector<Hero*>& allHeroes = _combatScene->_heroes;
		Vector<Soldier*>& allSoldiers = _combatScene->_soldiers;
		Vector<Actor*>& allTowers = _combatScene->_towers;
		for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && (*it) != _attackTarget && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
			{
				attackTarget2 = *it;
				break;
			}
		}
		if (!attackTarget2)
		{
			for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
			{
				if (_camp != (*it)->getCamp() && (*it) != _attackTarget && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
				{
					attackTarget2 = *it;
					break;
				}
			}
		}
		if (!attackTarget2)
		{
			for (auto it = allTowers.begin(); it != allTowers.end(); ++it)
			{
				if (_camp != (*it)->getCamp() && (*it) != _attackTarget && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
				{
					attackTarget2 = *it;
					break;
				}
			}
		}
		//
		for (auto it = allHeroes.begin(); it != allHeroes.end(); ++it)
		{
			if (_camp != (*it)->getCamp() && (*it) != attackTarget2 && (*it) != _attackTarget && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
			{
				attackTarget3 = *it;
				break;
			}
		}
		if (!attackTarget3)
		{
			for (auto it = allSoldiers.begin(); it != allSoldiers.end(); ++it)
			{
				if (_camp != (*it)->getCamp() && (*it) != _attackTarget && (*it) != attackTarget2 && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
				{
					attackTarget3 = *it;
					break;
				}
			}
		}
		if (!attackTarget3)
		{
			for (auto it = allTowers.begin(); it != allTowers.end(); ++it)
			{
				if (_camp != (*it)->getCamp() && (*it) != _attackTarget && (*it) != attackTarget2 && !(*it)->getAlreadyDead() && (*it)->getPosition().distance(this->getPosition()) <= this->getAttackRadius())
				{
					attackTarget3 = *it;
					break;
				}
			}
		}
		//
		if (_punishState < 3)
		{
			if (attackTarget2)
			{
				auto projectile = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.4, SPEED_FLY*0.8, this, attackTarget2);
				projectile->setScale(3.0f);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 2, projectile);
			}
			if (attackTarget3)
			{
				auto projectile = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.4, SPEED_FLY*0.9, this, attackTarget3);
				projectile->setScale(1.5f);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 1, projectile);
			}
		}
		else
		{
			if (attackTarget2)
			{
				auto projectile1 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.2, SPEED_FLY, this, attackTarget2);
				auto projectile2 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.2, SPEED_FLY*0.7, this, attackTarget2);
				auto projectile3 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.2, SPEED_FLY*0.4, this, attackTarget2);
				projectile1->setScale(1.5f);
				projectile2->setScale(1.5f);
				projectile3->setScale(1.5f);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 3, projectile1);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 6, projectile2);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 9, projectile3);
			}
			if (attackTarget3)
			{
				auto projectile1 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.2, SPEED_FLY, this, attackTarget3);
				auto projectile2 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.2, SPEED_FLY*0.7, this, attackTarget3);
				auto projectile3 = Projectile::create("pictures/others/RemoteSoldierArrow.png", _attack*0.2, SPEED_FLY*0.4, this, attackTarget3);
				projectile1->setScale(1.5f);
				projectile2->setScale(1.5f);
				projectile3->setScale(1.5f);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 3, projectile1);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 6, projectile2);
				_combatScene->_readyToLaunch.insert(nowTime + _minAttackInterval / 10 * 9, projectile3);
			}
		}


	}
	
	//考虑后裔宝宝的被动效果
	if (_punishState < 3)
	{
		//惩戒累计状态被不存在
		if (nowTime - _punishStateTime > 3)
		{
			_punishState = 1;
		}
		else
		{
			_punishState++;
		}
	}
	else
	{
		if (nowTime - _punishStateTime > 3)
		{
			_punishState = 1;
		}
	}
	_punishStateTime = nowTime;

	_lastAttackTime = nowTime;
	return true;
}

