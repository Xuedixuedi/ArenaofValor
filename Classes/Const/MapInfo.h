#ifndef __MAPINFO_H__
#define __MAPINFO_H__

#include "cocos2d.h"
#include "Constant.h"

class MapInfo
{
private:

	SizeINT _mapSize;

	SizeINT _tileSize;

	DyaDicVector _collisionBoard;

public:

	MapInfo() = default;

	MapInfo(TMXTiledMap* map);

	PointINT getGridPoint(const Vec2& position) const;

	Vec2 getPrecisePosition(const PointINT& girdPoint) const;

	bool checkCollision(const Vec2& position) const;
};

#endif // !__MAPINFO_H__
