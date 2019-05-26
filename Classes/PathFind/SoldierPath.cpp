#include "SoldierPath.h"
#include <fstream>
#include <random>


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
	std::ifstream OpenFile(filename);

	OpenFile >> _pointsCount;
	PointINT temp;
	for (int i=0; i < _pointsCount; ++i) 
	{
		OpenFile >> temp.x >> temp.y;
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

	_mapInfo = map;

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
			std::default_random_engine e;
			std::uniform_int_distribution<int> u(0, _pathGraph[minIndex].size());
			auto tempIndex = u(e);
			desVecPoint = _pathPoints[_pathGraph[minIndex][tempIndex]];
			log("newgirdPoint: %d, %d", desVecPoint.x, desVecPoint.y);
			auto res = _mapInfo.getPrecisePosition(desVecPoint);;
			log("newDest: %f, %f", res.x, res.y);
			return res;
		}
		else
		{
			return Vec2::ZERO;
		}
	}
	
	log("newgirdPoint: %d, %d", _pathPoints[minIndex].x, _pathPoints[minIndex].y);
	return _mapInfo.getPrecisePosition(_pathPoints[minIndex]);
}
