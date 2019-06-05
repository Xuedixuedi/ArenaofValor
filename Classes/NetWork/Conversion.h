#ifndef _CONVERSION_H_
#define _CONVERSION_H_
#include<iostream>
#include<cocos2d.h>

class Equipment;

class Conversion
{
public:
	Conversion();
	static bool strToBool(std::string str);
	static bool strToFloat(std::string str, float& f);
	static bool strToInt(std::string str, size_t& a);
	static bool strToPoint(std::string str, cocos2d::Point& pos);
	static bool strToEquip(std::string, Equipment* equip);
	static std::string floatToStr(float f);
	static std::string boolToStr(bool f);
	static std::string intToStr(size_t f);
	static std::string pointToStr(cocos2d::Point pos);

	~Conversion();
private:
	
};


#endif // !_CONVERSION_H_
