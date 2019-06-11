#include "SoldierPath.h"
#include <fstream>
#include <random>
#include <cmath>

SoldierPath* SoldierPath::create(const std::string& filename, MapInfo map)
{
	SoldierPath* soldierPath = new(std::nothrow)SoldierPath;
	if (soldierPath && soldierPath->init(filename, map))
	{
		soldierPath->autorelease();
		return soldierPath;
	}
	CC_SAFE_DELETE(soldierPath);
	return nullptr;
}

bool SoldierPath::init(const std::string& filename, MapInfo map)
{
	if (!Node::init())
	{
		return false;
	}
	//init

	srand((unsigned)time(NULL));

	_mapInfo = map;

	std::ifstream OpenFile(filename);
	OpenFile >> _pointsCount;
	PointINT temp;
	for (int i=0; i < _pointsCount; ++i) 
	{
		OpenFile >> temp.x >> temp.y;
		temp.y = _mapInfo.getMapSize().y - 1 - temp.y;
	//	log("%d %d", temp.x, temp.y);
		_pathPoints.push_back(temp);
	}


	INT32 state;
	_pathGraph.resize(_pointsCount);
	for (int i = 0; i < _pointsCount; ++i)
	{
		for (int j = 0; j < _pointsCount; ++j)
		{
			OpenFile >> state;
			if (state == 1)
			{
				_pathGraph[i].push_back(j);
			}
		}
	}

	return true;
}

INT32 vecDistanceSquare(PointINT P1, PointINT P2)
{
	return ((P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y));
}

Vec2 SoldierPath::getNextPoint(const Vec2& vecPoint)
{
	PointINT desVecPoint;
	auto gridPoint = _mapInfo.getGridPoint(vecPoint);
	INT32 minDis = 0;
	INT32 minIndex=-1;

	for (int i = 0; i < _pointsCount; ++i)
	{
		if (i == 0)
		{
			minDis = vecDistanceSquare(gridPoint, _pathPoints[0]);
			minIndex = 0;
		}
		else
		{
			auto dis = vecDistanceSquare(gridPoint, _pathPoints[i]);
			if (dis < minDis)
			{
				minDis = dis;
				minIndex = i;
			}
		}

		if (minDis == 0)
		{
			break;
		}
	}

	if (minDis == 0)
	{
		if (_pathGraph[minIndex].size())
		{

			auto tempIndex = rand()%_pathGraph[minIndex].size();
			//log("%d", tempIndex);
			desVecPoint = _pathPoints[_pathGraph[minIndex][tempIndex]];
			auto res = _mapInfo.getPrecisePosition(desVecPoint);;
			return res;
		}
		else
		{
			return Vec2::ZERO;
		}
	}
	
	return _mapInfo.getPrecisePosition(_pathPoints[minIndex]);
}
