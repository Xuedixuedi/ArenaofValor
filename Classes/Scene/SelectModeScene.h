#pragma once

#ifndef __SELECTMODE_SCENE_H__
#define __SELECTMODE_SCENE_H__

#include "cocos2d.h"


class SelectMode :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//·µ»Ø¼üºÍ1V1¼ü
	void menuBackCallBack(cocos2d::Ref *pSender);
	void menuSingleCallBack(cocos2d::Ref *pSender);
	void menuNetworkCallBack(cocos2d::Ref *pSender);
	void menu5v5CallBack(cocos2d::Ref *pSender);
	void menu1v1CallBack(cocos2d::Ref *pSender);
	void menuComingCallBack(cocos2d::Ref * pSender);
	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(SelectMode);
private:
	//Menu* _mu;
};

#endif