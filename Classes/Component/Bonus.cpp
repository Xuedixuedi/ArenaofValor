#include "Bonus.h"

Bonus::Bonus(float exp, int gold, Buff* buff):
	_exp(exp),
	_gold(gold),
	_buff(buff)
{
}

Bonus::~Bonus()
{
	if (_buff)
	{
		delete _buff;
		_buff = nullptr;
	}
}

void Bonus::increaseExp(float delta)
{
	_exp += delta;
}

void Bonus::increaseGold(int delta)
{
	_gold += delta;
}
