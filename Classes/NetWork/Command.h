#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <boost/asio.hpp>
#include "cocos2d.h"
#include "const/Constant.h"


USING_NS_CC;
using boost::asio::ip::tcp;

class Equipment;

class Command
{
public:
	Command(int numRows = 12);
	Command(std::string str, int numRos = 12);
	std::string CreateStrings();
	//
	int category;
	int player;
	//
	//std::string heroName;
	//包中对应的战斗过程的操作信息
	float standingAngle;
	bool isHeroMove;
	bool isHeroStopMove;
	bool isSkillLevelUp;
	int skillLevelUp;
	bool isGetEquip;
	EEQUIPMENT getEquip;
	bool isSellEquip;
	int sellEquip;
	bool isCastSkill;
	int castSkill;
	bool isSkillParamter;
	cocos2d::Point skillParamter;
	bool isAttack;
	std::string heroName;
	//用于传输的字符串数组
	int numRows;
	std::vector <std::string> package;
	void reset();
private:
	//将package中字符串转换成数据
	void createCommand();

};

#endif // !_MESSAGE_H_