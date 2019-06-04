#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h" 
#include "Const/Constant.h"
#include <functional>

USING_NS_CC;
//枚举型：用于标识摇杆与摇杆的背景  
#define TAG_ROCKER     0
#define TAG_ROCKERBG   1

class HRocker : public Layer
{
	CC_SYNTHESIZE(bool, isCanMove, IsCanMove);
	CC_SYNTHESIZE(float, _angle, Angle);

public:
	//创建摇杆，摇杆图片，摇杆背景图片，起始坐标  
	static HRocker* createHRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//启动摇杆  
	void startRocker(bool _isStopOther);
	//停止摇杆  
	void stopRocker();
private:
	EventListenerTouchOneByOne* listener;
	EventListenerKeyboard* listenerKeyBoard;
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//得到半径为r的圆周运动上一个角度应对应的x,y坐标  
	Point getAnglePosition(float r, float angle);
	//摇杆背景的坐标  
	Point rockerBGPosition;
	//摇杆背景的半径  
	float rockerBGR;
	//触屏事件  
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	//按键状态
	bool _wState, _aState, _sState, _dState;
	EDirection _direction;
	//按键事件
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, int type);
	virtual bool updateDirection();
	CREATE_FUNC(HRocker);
};

#endif  