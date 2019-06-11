#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <boost/asio.hpp>
#include<cocos2d.h>
using boost::asio::ip::tcp;

class Equipment;

class Command
{
public:
	Command(size_t numRows = 12);
	Command(std::string str, size_t numRos = 12);
	std::string CreateStrings();
	//
	size_t category;
	size_t player;
	//
	//std::string heroName;
	//包中对应的战斗过程的操作信息
	float standingAngle;
	bool isHeroMove;
	bool isHeroStopMove;
	bool isSkillLevelUp;
	size_t skillLevelUp;
	bool isGetEquip;
	Equipment* getEquip;
	bool isSellEquip;
	Equipment* sellEquip;
	bool isCastSkill;
	size_t castSkill;
	bool isSkillParamter;
	cocos2d::Point skillParamter;
	bool isAttack;
	std::string heroName;
	//用于传输的字符串数组
	size_t numRows;
	std::vector <std::string> package;
private:
	//将package中字符串转换成数据
	void createCommand();

};

#endif // !_MESSAGE_H_
