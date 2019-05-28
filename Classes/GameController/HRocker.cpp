#include "HRocker.h"
#include <functional>


HRocker* HRocker::createHRocker(const char* rockerImageName, const char* rockerBGImageName, Point position)
{
	HRocker* layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
void HRocker::rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position)
{
	//添加摇杆背景图  
	Sprite* spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setVisible(false);
	spRockerBG->setPosition(position);
	addChild(spRockerBG, 0, TAG_ROCKERBG);
	//添加摇杆上方那个可移动的图  
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setVisible(false);
	spRocker->setPosition(position);
	addChild(spRocker, 1, TAG_ROCKER);
	spRocker->setOpacity(180);
	//摇杆背景图坐标  
	rockerBGPosition = position;
	//摇杆背景图半径  
	rockerBGR = spRockerBG->getContentSize().width * 0.5;
	listener = EventListenerTouchOneByOne::create();
	listenerKeyBoard = EventListenerKeyboard::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);

	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(HRocker::onPressKey, this);
	listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(HRocker::onReleaseKey, this);

	listener->setSwallowTouches(true);
}
//启动摇杆  
void HRocker::startRocker(bool _isStopOther)
{
	//精灵设置可见，设置监听  
	Sprite* rocker = (Sprite*)getChildByTag(TAG_ROCKER);
	rocker->setVisible(true);
	Sprite* rockerBG = (Sprite*)getChildByTag(TAG_ROCKERBG);
	rockerBG->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener->clone(), 2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
}
//停止摇杆  
void HRocker::stopRocker()
{
	//精灵设置不可见，取消监听  
	Sprite* rocker = (Sprite*)getChildByTag(TAG_ROCKER);
	rocker->setVisible(false);
	Sprite* rockerBG = (Sprite*)getChildByTag(TAG_ROCKERBG);
	rockerBG->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}
//得到两坐标的角度值  
float HRocker::getRad(Point pos1, Point pos2)
{
	//得到两点的坐标x,y坐标值  
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//求出两边长度  
	float x = px2 - px1;
	float y = py1 - py2;
	//开方   与  几次方 公式  
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / xie;
	//反余弦定理，知道两边长求角度：cos = 邻边/斜边  
	float rad = acos(cos);
	//当触屏Y坐标 <摇杆的Y坐标时，取反值  
	if (py1 > py2)
	{
		rad = 2 * M_PI - rad;
	}
	return rad;
}
//得到与角度对应的半径为r的圆上一坐标点  
Point HRocker::getAnglePosition(float r, float angle)
{
	return ccp(r * cos(angle), r * sin(angle));
}
bool HRocker::onTouchBegan(Touch* touch, Event* event)
{

	Sprite* sp = (Sprite*)getChildByTag(TAG_ROCKER);
	//得到触屏点坐标  
	Point point = touch->getLocation();
	//判断是否点击到sp这个精灵：boundingBox()精灵大小之内的所有坐标  
	if (sp->boundingBox().containsPoint(point))
	{
		isCanMove = true;
		return true;
	}
	isCanMove = false;
	return false;
}
void HRocker::onTouchMoved(Touch* touch, Event* event)
{
	if (!isCanMove)
	{
		return;
	}
	Sprite* sp = (Sprite*)getChildByTag(TAG_ROCKER);
	Point point = touch->getLocation();
	_angle = getRad(rockerBGPosition, point);
	//判断两个圆心的距离是否大于摇杆背景的半径  
	if (sqrt(pow(point.x - rockerBGPosition.x, 2) + pow(point.y - rockerBGPosition.y, 2)) >= rockerBGR)
	{
		//确保小圆运动范围在背景圆内  
		sp->setPosition(ccpAdd(getAnglePosition(rockerBGR, _angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
	}
	else
	{
		//触点在背景圆内则跟随触点运动
		sp->setPosition(point);
	}
}
void HRocker::onTouchEnded(Touch* touch, Event* event)
{
	if (!isCanMove)
	{
		return;
	}
	Sprite* rocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* rockerBG = (Sprite*)getChildByTag(TAG_ROCKERBG);
	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08, rockerBG->getPosition()));

	isCanMove = false;
}
bool HRocker::onPressKey(EventKeyboard::KeyCode keyCode, Event* envet)
{
	updateState(keyCode, PRESS);
	Sprite* rocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* rockerBG = (Sprite*)getChildByTag(TAG_ROCKERBG);
	rocker->stopAllActions();
	isCanMove = true;
	Point point;

	if (_direction == EDirection::NODIR)
	{
		isCanMove = false;
		return false;
	}

	switch (_direction)
	{
	case EDirection::DOWN:
	{
		point = Point(rockerBGPosition.x, rockerBGPosition.y - rockerBGR);
		break;
	}
	case EDirection::DOWNLEFT:
	{
		point = Point(rockerBGPosition.x - rockerBGR, rockerBGPosition.y - rockerBGR);
		break;
	}
	case EDirection::DOWNRIGHT:
	{
		point = Point(rockerBGPosition.x + rockerBGR, rockerBGPosition.y - rockerBGR);
		break;
	}
	case EDirection::UP:
	{
		point = Point(rockerBGPosition.x, rockerBGPosition.y + rockerBGR);
		break;
	}
	case EDirection::UPLEFT:
	{
		point = Point(rockerBGPosition.x - rockerBGR, rockerBGPosition.y + rockerBGR);
		break;
	}
	case EDirection::UPRIGHT:
	{
		point = Point(rockerBGPosition.x + rockerBGR, rockerBGPosition.y + rockerBGR);
		break;
	}
	case EDirection::LEFT:
	{
		point = Point(rockerBGPosition.x - rockerBGR, rockerBGPosition.y);
		break;
	}
	case EDirection::RIGHT:
	{
		point = Point(rockerBGPosition.x + rockerBGR, rockerBGPosition.y);
		break;
	}
	}

	_angle = getRad(rockerBGPosition, point);
	rocker->setPosition(ccpAdd(getAnglePosition(rockerBGR, _angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
	return true;
}

bool HRocker::onReleaseKey(EventKeyboard::KeyCode keyCode, Event * envet)
{
	updateState(keyCode, RELEASE);
	if (!isCanMove)
	{
		return true;
	}
	if (_direction == EDirection::NODIR)
	{
		Sprite* rocker = (Sprite*)getChildByTag(TAG_ROCKER);
		Sprite* rockerBG = (Sprite*)getChildByTag(TAG_ROCKERBG);
		rocker->stopAllActions();
		rocker->runAction(MoveTo::create(0.08, rockerBG->getPosition()));
		isCanMove = false;
	}
	else
	{
		Sprite* rocker = (Sprite*)getChildByTag(TAG_ROCKER);
		Sprite* rockerBG = (Sprite*)getChildByTag(TAG_ROCKERBG);
		rocker->stopAllActions();
		isCanMove = true;
		Point point;
		switch (_direction)
		{
		case EDirection::DOWN:
		{
			point = Point(rockerBGPosition.x, rockerBGPosition.y - rockerBGR);
			break;
		}
		case EDirection::DOWNLEFT:
		{
			point = Point(rockerBGPosition.x - rockerBGR, rockerBGPosition.y - rockerBGR);
			break;
		}
		case EDirection::DOWNRIGHT:
		{
			point = Point(rockerBGPosition.x + rockerBGR, rockerBGPosition.y - rockerBGR);
			break;
		}
		case EDirection::UP:
		{
			point = Point(rockerBGPosition.x, rockerBGPosition.y + rockerBGR);
			break;
		}
		case EDirection::UPLEFT:
		{
			point = Point(rockerBGPosition.x - rockerBGR, rockerBGPosition.y + rockerBGR);
			break;
		}
		case EDirection::UPRIGHT:
		{
			point = Point(rockerBGPosition.x + rockerBGR, rockerBGPosition.y + rockerBGR);
			break;
		}
		case EDirection::LEFT:
		{
			point = Point(rockerBGPosition.x - rockerBGR, rockerBGPosition.y);
			break;
		}
		case EDirection::RIGHT:
		{
			point = Point(rockerBGPosition.x + rockerBGR, rockerBGPosition.y);
			break;
		}
		case EDirection::NODIR:
		{
			point = Point(rockerBGPosition.x, rockerBGPosition.y);
			break;
		}
		default:
		{
			point = Point(rockerBGPosition.x, rockerBGPosition.y);
			break;
		}
		}
		_angle = getRad(rockerBGPosition, point);
		rocker->setPosition(ccpAdd(getAnglePosition(rockerBGR, _angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
	}

	return true;
}

bool HRocker::updateState(EventKeyboard::KeyCode keyCode, int type)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	{
		if (type == PRESS)
		{
			_wState = true;
			_sState = false;
		}
		else if (type == RELEASE)
		{
			_wState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		if (type == PRESS)
		{
			_aState = true;
			_dState = false;
		}
		else if (type == RELEASE)
		{
			_aState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		if (type == PRESS)
		{
			_sState = true;
			_wState = false;
		}
		else if (type == RELEASE)
		{
			_sState = false;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		if (type == PRESS)
		{
			_dState = true;
			_aState = false;
		}
		else if (type == RELEASE)
		{
			_dState = false;
		}
		break;
	}
	default:
		break;
	}
	updateDirection();
	return true;
}

bool HRocker::updateDirection()
{
	if (_wState)
	{
		if (_aState)
		{
			_direction = EDirection::UPLEFT;
		}
		else if (_dState)
		{
			_direction = EDirection::UPRIGHT;
		}
		else
		{
			_direction = EDirection::UP;
		}
	}
	else if (_sState)
	{
		if (_aState)
		{
			_direction = EDirection::DOWNLEFT;
		}
		else if (_dState)
		{
			_direction = EDirection::DOWNRIGHT;
		}
		else
		{
			_direction = EDirection::DOWN;
		}
	}
	else
	{
		if (_aState)
		{
			_direction = EDirection::LEFT;
		}
		else if (_dState)
		{
			_direction = EDirection::RIGHT;
		}
		else
		{
			_direction = EDirection::NODIR;
		}
	}
	return true;
}