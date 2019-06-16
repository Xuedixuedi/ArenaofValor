#ifndef __CHATBOX_H__
#define __CHATBOX_H__

#include "cocos2d.h"
#include <vector>
#include <string>
#include "Const/Constant.h"

class Chatbox :public Sprite
{
	CC_SYNTHESIZE(std::string, _message, Message);

private:

	std::vector<std::string> _messages;
	Label* _labelMessages[CHATBOX_SIZE];
	Label* _labelInputMessage;
	std::string _defaultHeroName;
	size_t _messageSize;

public:

	static char switchKeycodeToChar(EventKeyboard::KeyCode keyCode);
	void setDefaultHeroName(std::string heroName);
	void updateMessage(char newChar);
	void pushMessage(std::string newMessage = "");
	virtual bool init();
	CREATE_FUNC(Chatbox);
};
#endif // !__CHATBOX_H__
