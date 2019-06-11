#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"

class MapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	CREATE_FUNC(MapScene);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	cocos2d::CCPoint positionToTileCoord(cocos2d::CCPoint cocosCoord);

	typedef enum {
		Moveble = 0,
		Wall = 1,
		Enemy = 2
	}CollisionType;

	MapScene::CollisionType checkCollision(cocos2d::CCPoint heroPotion);

private:
	cocos2d::Size visibleSize;
	cocos2d::Sprite *sprite;
	cocos2d::TMXTiledMap *map;
	cocos2d::LabelTTF *label;
	cocos2d::TMXLayer* collidable;


};


#endif