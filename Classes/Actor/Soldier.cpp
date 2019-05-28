#include "Soldier.h"

Soldier* Soldier::create(EAttackMode attackMode, ECamp camp, ERoad road, GameScene* scene)
{
	Soldier* soldier = new(std::nothrow)Soldier;
	if (soldier && soldier->init(attackMode, camp, road, scene))
	{
		soldier->autorelease();
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}

bool Soldier::init(EAttackMode attackMode, ECamp camp, ERoad road, GameScene* scene)
{
	if (!Sprite::init())
	{
		return false;
	}
	_combatScene = scene;
	initData(attackMode,camp,road);
	initHealthComp();
	return true;
}

void Soldier::initData(EAttackMode attackMode, ECamp camp, ERoad road)
{
	//初始化

	//根据攻击模式和阵营初始化纹理
	if (camp == ECamp::BLUE)
	{
		if (attackMode == EAttackMode::MELEE)
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
		else if (attackMode == EAttackMode::REMOTE)
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
		else
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
	}
	else if (camp == ECamp::RED)
	{
		if (attackMode == EAttackMode::MELEE)
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
		else if (attackMode == EAttackMode::REMOTE)
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
		else
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
	}
	else
	{
		if (attackMode == EAttackMode::MELEE)
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
		else if (attackMode == EAttackMode::REMOTE)
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
		else
		{
			setTexture("pictures\\soldier\\BlueDown.png");

		}
	}

	_camp = camp;

	_defense = SOLDIER_ARMOR;
	_magicDefense = SOLDIER_MAGIC_DEFENSE;
	_attack = SOLDIER_ATTACK;
	_attackRadius = attackMode == EAttackMode::MELEE ? DEFAULT_ATTACK_RADIUS_MELEE : DEFAULT_ATTACK_RADIUS_REMOTE;
	
	_lastAttackTime = 0;
	_lastAttackFrom = NULL;
	_attackTarget = NULL;
	
	_alreadyDead = false;
	
	_moveSpeed = SOLDIER_MOVE_SPEED;
	_isMovingToDest = false;
	
	_isArrivedFirstDest = false;
	_isDisturbed = false;

	if (camp == ECamp::BLUE)
	{
		if (road = ERoad::DOWNWAY)
		{
			_direction = EDirection::RIGHT;
			_standingAngle = 0.f;
		}
		else if (road == ERoad::MIDWAY)
		{
			_direction = EDirection::UPRIGHT;
			_standingAngle = 2 * MIN_DEGREE_IN_RAD;
		}
		else
		{
			_direction = EDirection::UP;
			_standingAngle = 4 * MIN_DEGREE_IN_RAD;
		}
	}
	else
	{
		if (road = ERoad::DOWNWAY)
		{
			_direction = EDirection::DOWN;
			_standingAngle = 12 * MIN_DEGREE_IN_RAD;
		}
		else if (road == ERoad::MIDWAY)
		{
			_direction = EDirection::DOWNLEFT;
			_standingAngle = 10 * MIN_DEGREE_IN_RAD;
		}
		else
		{
			_direction = EDirection::LEFT;
			_standingAngle = 8 * MIN_DEGREE_IN_RAD;
		}
	}
}

void Soldier::initHealthComp()
{
	_healthComp = StateComponent::create(EStateType::HEALTH, SOLDIER_HP, 0);
	auto position = getPosition();
	auto size = getBoundingBox().size;

	_healthComp->setScaleX(1.2);
	_healthComp->setScaleY(2.5);
	_healthComp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_healthComp->setPosition(position + Vec2(size.width / 2, size.height * 2 / 3));
	addChild(_healthComp);
}

