#pragma once
#ifndef __SELECTHERO_SCENE_H__
#define __SELECTHERO_SCENE_H__

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "cocos2d.h"
#include "Const/Constant.h"
class chat_client;

class SelectHero :public cocos2d::Scene
{
public:

	std::stack<std::string> heroList;

	static cocos2d::Scene* createScene(chat_client* client, int PlayerNumber);

	virtual bool init(chat_client* client, int PlayerNumber);
	//netWork
	chat_client* _client;
	int _playerNumber;
	void update(float delta);
	std::string _selecterHero;
	bool _haveSelected_0;
	bool _haveSelected_1;
	std::vector<HeroMessage> _heroMessages;
	std::map<int, std::string >_map;
	//
	//想把三个英雄现在分开的menu写成三个相关联的单选框 监视调用哪个单选框决定确定时的动作



	void menuHouyiCallBack(cocos2d::Ref* pSender);
	void menuDajiCallBack(cocos2d::Ref* pSender);
	void menuYaseCallBack(cocos2d::Ref* pSender);

	void menuBackCallBack(cocos2d::Ref* pSender);


private:
	std::stack<std::string> selectedHero;//选择的英雄

};

#endif