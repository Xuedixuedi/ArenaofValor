#ifndef __SOLDIERPATH_H__
#define __SOLDIERPATH_H__

#include "cocos2d.h"
#include <vector>
#include <iostream>
#include <vector>
#include "Const/MapInfo.h"

USING_NS_CC;

class SoldierPath :public Node
{

private:

	INT32 _pointsCount;

	std::vector<PointINT> _pathPoints;

	std::vector<std::vector<INT32>> _pathGraph;

	MapInfo _mapInfo;

public:

	virtual Vec2 getNextPoint(const Vec2& vecPoint); 

	virtual bool init(const std::string& filename, MapInfo map);

	static SoldierPath* create(const std::string& filename, MapInfo map);


};

#endif // !__SOLDIERPATH_H__
