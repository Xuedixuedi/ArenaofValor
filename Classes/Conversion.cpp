#include"Conversion.h"

Conversion::Conversion()
{

}

Conversion::~Conversion()
{

}
std::vector<std::string> & Conversion::split(const std::string &str, char delim,
	std::vector<std::string> &elems, bool skip_empty)
{
	std::istringstream iss(str);
	for (std::string item; std::getline(iss, item, delim); )
		if (skip_empty && item.empty()) continue;
		else elems.push_back(item);
	return elems;
}
bool Conversion::strToBool(std::string str)
{
	if (str == "true")
		return true;
	else
		return false;
}

bool Conversion::strToFloat(std::string str, float&f)
{
	if (str == "")
	{
		f = NULL;
		return false;
	}
	else
	{
		std::stringstream stream(str);
		stream >> f;
		return true;
	}
}

bool Conversion::strToInt(std::string str, size_t & a)
{
	if (str == "")
	{
		a = NULL;
		return false;
	}
	else
	{
		a = std::stoi(str);
		return true;
	}
}

bool Conversion::strToPoint(std::string str, cocos2d::Point& pos)
{
	if (str == "")
		return false;
	std::vector<std::string> result;
	Conversion::split(str, ',', result);
	float a, b;
	std::stringstream stream_1(result[0]);
	std::stringstream stream_2(result[1]);
	stream_1 >> a;
	stream_2 >> b;
	pos = cocos2d::Point(a, b);
	return true;
}

bool Conversion::strToEquip(std::string, Equipment * equip)
{
	return false;
}

std::string Conversion::floatToStr(float f)
{
	std::stringstream stream;
	stream << f;
	return stream.str();
}

std::string Conversion::boolToStr(bool f)
{
	std::string str;
	if (f)
		str = "true";
	else
		str = "false";
	return str;
}

std::string Conversion::intToStr(size_t f)
{
	std::stringstream stream;
	stream << f;
	return stream.str();
}

std::string Conversion::pointToStr(cocos2d::Point pos)
{
	std::string str;
	std::stringstream stream_1;
	std::stringstream stream_2;
	stream_1 << pos.x;
	stream_2 << pos.y;
	str = stream_1.str() + ',' + stream_2.str();
	return str;
}


