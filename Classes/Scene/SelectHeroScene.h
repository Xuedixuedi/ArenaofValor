#pragma once

#ifndef __SELECTHERO_SCENE_H__
#define __SELECTHERO_SCENE_H__

#include <iostream>
#include <stack>
#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class SelectHero :public cocos2d::Scene
{
public:


	static cocos2d::Scene* createScene();

	virtual bool init();


	//想把三个英雄现在分开的menu写成三个相关联的单选框 监视调用哪个单选框决定确定时的动作



	void menuHouyiCallBack(cocos2d::Ref *pSender);
	void menuDajiCallBack(cocos2d::Ref *pSender);
	void menuYaseCallBack(cocos2d::Ref *pSender);

	void menuBackCallBack(cocos2d::Ref *pSender);

	CREATE_FUNC(SelectHero);

private:
	std::stack<std::string> selectedHero;//选择的英雄

};

#endif