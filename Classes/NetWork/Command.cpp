#include <vector>
#include"Command.h"
#include"Conversion.h"


Command::Command(int num)
{
	numRows = num;
	reset();
}

Command::Command(std::string str, int num)
{
	numRows = num;
	Conversion::split(str, '@', package);
	createCommand();
}

std::string Command::CreateStrings()
{
	package.resize(numRows);
	for (int i = 0; i < numRows; ++i)
	{
		package[i] = "";
	}
	package[0] = Conversion::intToStr(category);
	package[1] = Conversion::intToStr(player);
	//
	package[2] = Conversion::floatToStr(standingAngle);
	package[3] = Conversion::boolToStr(isHeroMove);
	package[4] = Conversion::boolToStr(isHeroStopMove);
	package[5] = Conversion::intToStr(skillLevelUp);
	package[6] = Conversion::equipToStr(getEquip);
	package[7] = Conversion::intToStr(sellEquip);
	package[8] = Conversion::intToStr(castSkill);
	package[9] = Conversion::pointToStr(skillParamter);
	package[10] = Conversion::boolToStr(isAttack);
	package[11] = heroName;

	package[12] = Conversion::intToStr(frames);
	package[13] = chatMsg;
	if (chatMsg != "*")
	{
		_isChatMsg = true;
	}
	std::string result;
	for (int i = 0; i < numRows; ++i)
	{
		if (i != 0)
		{
			result += '@';
		}
		result += package[i];
	}
	return result;
}


void Command::createCommand()
{
	Conversion::strToInt(package[0], category);
	Conversion::strToInt(package[1], player);
	Conversion::strToFloat(package[2], standingAngle);
	isHeroMove = Conversion::strToBool(package[3]);
	isHeroStopMove = Conversion::strToBool(package[4]);
	isSkillLevelUp = Conversion::strToInt(package[5], skillLevelUp);
	isGetEquip = Conversion::strToEquip(package[6], getEquip);
	isSellEquip = Conversion::strToInt(package[7], sellEquip);
	isCastSkill = Conversion::strToInt(package[8], castSkill);
	isSkillParamter = Conversion::strToPoint(package[9], skillParamter);
	isAttack = Conversion::strToBool(package[10]);
	heroName = package[11];
	Conversion::strToInt(package[12], frames);
	chatMsg = package[13];
	if (package[13] == "*")
		_isChatMsg = false;
	else
		_isChatMsg = true;
}

void Command::reset()
{
	standingAngle = -1.f;
	player = 0;
	isHeroMove = false;
	isHeroStopMove = false;
	isSkillLevelUp = false;
	skillLevelUp = -1;
	isGetEquip = false;
	getEquip = EEQUIPMENT::NOTHING;
	isSellEquip = false;
	sellEquip = -1;
	isCastSkill = false;
	castSkill = -1;
	isSkillParamter = false;
	skillParamter = Point::ZERO;
	isAttack = false;
	heroName = "fuck";
	frames = -1;
	chatMsg = "*";
	_isChatMsg = false;
}
