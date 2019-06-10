#pragma once

#ifndef __SELECTENEMYHERO_SCENE_H__
#define __SELECTENEMYHERO_SCENE_H__

#include <iostream>
#include "cocos2d.h"

class SelectEnemyHero :public cocos2d::Scene
{
public:


	static cocos2d::Scene* createScene();

	virtual bool init();


	//想把三个英雄现在分开的menu写成三个相关联的单选框 监视调用哪个单选框决定确定时的动作



	void menuHouyiCallBack(cocos2d::Ref *pSender);
	void menuDajiCallBack(cocos2d::Ref *pSender);
	void menuYaseCallBack(cocos2d::Ref *pSender);

	void menuBackCallBack(cocos2d::Ref *pSender);

	CREATE_FUNC(SelectEnemyHero);

private:
	std::string _heroName;

};

#endif