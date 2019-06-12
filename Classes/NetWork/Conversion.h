#ifndef _CONVERSION_H_
#define _CONVERSION_H_
#include<iostream>
#include<cocos2d.h>
#include"Const/Constant.h"
class Equipment;

class Conversion
{
public:
	Conversion();
	static bool strToBool(std::string str);
	static bool strToFloat(std::string str, float& f);
	static bool strToInt(std::string str, int& a);
	static bool strToPoint(std::string str, cocos2d::Point& pos);
	static bool strToEquip(std::string str, EEQUIPMENT& equip);
	static std::string equipToStr(EEQUIPMENT equip);
	static std::string floatToStr(float f);
	static std::string boolToStr(bool f);
	static std::string intToStr(int f);
	static std::string pointToStr(cocos2d::Point pos);
	static std::vector<std::string> & split(const std::string &str, char delim,
		std::vector<std::string> &elems, bool skip_empty = true);
	~Conversion();
private:
	
};


#endif // !_CONVERSION_H_