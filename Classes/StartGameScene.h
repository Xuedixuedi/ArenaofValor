#pragma once

#include "cocos2d.h"

#ifndef __STARTGAME_SCENE_H__
#define __STARTFAME_SCENE_H__

class StartGame : public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//¿ªÊ¼ÓÎÏ·¼ü
	void menuStartCallBack(cocos2d::Ref *pSender);

	CREATE_FUNC(StartGame);

};

#endif