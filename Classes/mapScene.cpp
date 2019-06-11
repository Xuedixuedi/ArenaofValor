#include "mapScene.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MapScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	map = TMXTiledMap::create("map/2.tmx");
	map->setAnchorPoint(ccp(0.5, 0.5));
	map->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	//map->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	addChild(map);

	// 获取 objLayer 对象层
	TMXObjectGroup *objGroup = map->objectGroupNamed("hero");
	// 获取 hero 对象
	auto vm = objGroup->objectNamed("haha");
	float x = vm.at("x").asFloat();
	float y = vm.at("y").asFloat();

	String name = vm.at("name").asString();
	log(" name %s ", name);



	// 在 hero 的位置处添加精灵
	sprite = Sprite::create("map/houyi.png");
	sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	// 因为地图的锚点是左下角，所以设置精灵的锚点也为左下角，这样位置才能对应上
	sprite->setAnchorPoint(Vec2::ZERO);
	addChild(sprite);

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}

//将精灵坐标转化为地图坐标
CCPoint MapScene::positionToTileCoord(cocos2d::CCPoint cocosCoord)
{
	int x = cocosCoord.x / map->getTileSize().width;
	int y = (((map->getMapSize().height - 1)*map->getTileSize().height) - cocosCoord.y) / map->getTileSize().height;
	return ccp(x, y);
}

MapScene::CollisionType MapScene::checkCollision(CCPoint heroPotion)
{
	cocos2d::CCPoint tileCoord = positionToTileCoord(heroPotion);

	//检测是否超出地图边界
	if (tileCoord.x<0 || tileCoord.x>map->getMapSize().width - 1 ||
		tileCoord.y<0 || tileCoord.y>map->getMapSize().height - 1)
		return Wall;

	//判定目标坐标是否为墙壁
	int tileGid = map->layerNamed("wall")->tileGIDAt(tileCoord);
	if (tileGid) {
		return Wall;
	}
	return Moveble;
}



bool MapScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Vec2 pos = touch->getLocation();

	Vec2 spritePos = sprite->getPosition();
	Vec2 diff = pos - spritePos;//触摸点和精灵位置之差

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0)//点在右边
		{
			spritePos.x += map->getTileSize().width;
			sprite->runAction(FlipX::create(false));
		}
		else
		{
			spritePos.x -= map->getTileSize().width;
			sprite->runAction(FlipX::create(true));
		}
	}
	else
	{
		if (diff.y > 0)
		{
			spritePos.y += map->getTileSize().height;
			sprite->runAction(FlipY::create(false));
		}
		else
		{
			spritePos.y -= map->getTileSize().height;
			sprite->runAction(FlipY::create(true));
		}
	}
	sprite->setPosition(spritePos);

	cocos2d::CCPoint targetPosition = ccpAdd(sprite->getPosition(), spritePos);
	if (checkCollision(targetPosition) == 1)
	{
		return 0;
	}

	//ActionInstant *func = CallFunc::create(this, callfunc_selector(MapScene::judgeCollide));
	//sprite->runAction(Sequence::create(MoveTo::create(1, pos), func, nullptr));
	return true;
}
