#include <vector>
#include"Message.h"
#include"Conversion.h"
Message::Message(size_t numRows)
{
	
}

void Message::CreateStrings()
{
	for (int i = 0; i < numRows; ++i)
	{
		std::string tmp = "";
		package.push_back(tmp);
	}
	package[0] = Conversion::floatToStr(standingAngle);
	package[1] = Conversion::boolToStr(isHeroMove);
	package[2] = Conversion::boolToStr(isHeroStopMove);
	if (isSkillLevelUp)
	{
		package[3] = Conversion::intToStr(skillLevelUp);
	}
	if (isGetEquip)
	{
		package[4] = Conversion::floatToStr(standingAngle);
	}
	if (isSellEquip)
	{
		package[5] = Conversion::floatToStr(standingAngle);
	}
	if (isCastSkill)
	{
		package[6] = Conversion::intToStr(castSkill);
	}
	if (isCastSkill&&isSkillParamter)
	{
		package[7] = Conversion::pointToStr(skillParamter);
	}
	package[8] = Conversion::boolToStr(isAttack);
}

Message::Message(boost::asio::ip::tcp::iostream& io, size_t numRows )
{
	for (int i = 0; i < numRows; ++i)
	{
		std::string tmp;
		std::getline(io, tmp);
		package.push_back(tmp);
	}
	createCommand();
}
void Message::createCommand()
{
	Conversion::strToFloat(package[0],standingAngle);
	isHeroMove = Conversion::strToBool(package[1]);
	isHeroStopMove = Conversion::strToBool(package[2]);
	isSkillLevelUp = Conversion::strToInt(package[3], skillLevelUp);
	//TODO : Equip*2
	isCastSkill = Conversion::strToInt(package[6], castSkill);
	isSkillParamter = Conversion::strToPoint(package[7], skillParamter);
	isAttack = Conversion::strToBool(package[8]);
}
