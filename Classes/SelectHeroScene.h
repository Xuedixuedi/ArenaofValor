#pragma once


#include "cocos2d.h"

#ifndef __SELECTHERO_SCENE_H__
#define __SELECTHERO_SCENE_H__

class SelectHeroScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	void menuHouyiCallBack(cocos2d::Ref *pSender);
	void menuDajiCallBack(cocos2d::Ref *pSender);
	void menuYaseCallBack(cocos2d::Ref *pSender);

	void menuBackCallBack(cocos2d::Ref *pSender);
	void menuOKCallBack(cocos2d::Ref *pSender);

	CREATE_FUNC(SelectHeroScene);

};

#endif