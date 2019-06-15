#include "Chatbox.h"

bool Chatbox::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	_messages = std::vector<std::string>(CHATBOX_SIZE, "");
	_messageSize = 0;
	setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	setTexture("pictures/others/ChatboxBG.png");
	_defaultHeroName = "";
	_message = "";
	_labelInputMessage = Label::create("", "fonts/HELVETICAEXT-NORMAL.TTF", 15);
	_labelInputMessage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelInputMessage->setPosition(Vec2(20, 44.5));
	addChild(_labelInputMessage);
	for (int i = 0; i < CHATBOX_SIZE; ++i)
	{
		_labelMessages[i] = Label::create(_messages[i], "fonts/HELVETICAEXT-NORMAL.TTF", 15);
		_labelMessages[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_labelMessages[i]->setPosition(Vec2(20, (CHATBOX_SIZE + 1 - i) * 44.5));
		addChild(_labelMessages[i]);
	}

	return true;
}

char Chatbox::switchKeycodeToChar(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	//case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
	//	break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
	//	break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_DELETE:
	//	break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
	//	break;
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		return '0';
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		return '1';
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		return '2';
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		return '3';
	case cocos2d::EventKeyboard::KeyCode::KEY_4:
		return '4';
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		return '5';
	case cocos2d::EventKeyboard::KeyCode::KEY_6:
		return '6';
	case cocos2d::EventKeyboard::KeyCode::KEY_7:
		return '7';
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		return '8';
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		return '9';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
		return 'A';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_B:
		return 'B';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_C:
		return 'C';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
		return 'D';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_E:
		return 'E';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_F:
		return 'F';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_G:
		return 'G';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_H:
		return 'H';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_I:
		return 'I';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_J:
		return 'J';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_K:
		return 'K';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_L:
		return 'L';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_M:
		return 'M';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_N:
		return 'N';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_O:
		return 'O';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_P:
		return 'P';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Q:
		return 'Q';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_R:
		return 'R';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
		return 'S';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_T:
		return 'T';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_U:
		return 'U';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_V:
		return 'V';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
		return 'W';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_X:
		return 'X';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Y:
		return 'Y';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Z:
		return 'Z';
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		return 'a';
	case cocos2d::EventKeyboard::KeyCode::KEY_B:
		return 'b';
	case cocos2d::EventKeyboard::KeyCode::KEY_C:
		return 'c';
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		return 'd';
	case cocos2d::EventKeyboard::KeyCode::KEY_E:
		return 'e';
	case cocos2d::EventKeyboard::KeyCode::KEY_F:
		return 'f';
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		return 'g';
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		return 'h';
	case cocos2d::EventKeyboard::KeyCode::KEY_I:
		return 'i';
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		return 'j';
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		return 'k';
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		return 'l';
	case cocos2d::EventKeyboard::KeyCode::KEY_M:
		return 'm';
	case cocos2d::EventKeyboard::KeyCode::KEY_N:
		return 'n';
	case cocos2d::EventKeyboard::KeyCode::KEY_O:
		return 'o';
	case cocos2d::EventKeyboard::KeyCode::KEY_P:
		return 'p';
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:
		return 'q';
	case cocos2d::EventKeyboard::KeyCode::KEY_R:
		return 'r';
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		return 's';
	case cocos2d::EventKeyboard::KeyCode::KEY_T:
		return 't';
	case cocos2d::EventKeyboard::KeyCode::KEY_U:
		return 'u';
	case cocos2d::EventKeyboard::KeyCode::KEY_V:
		return 'v';
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		return 'w';
	case cocos2d::EventKeyboard::KeyCode::KEY_X:
		return 'x';
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		return 'y';
	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
		return 'z';
	default:
		return '*';
		break;
	}
	return 0;
}

void Chatbox::setDefaultHeroName(std::string heroName)
{
	_defaultHeroName = heroName + " :";
	_message = _defaultHeroName;
}

void Chatbox::updateMessage(char newChar)
{
	if (_messageSize<15 && newChar != '*')
	{
		++_messageSize;
		_message += newChar;
		_labelInputMessage->setString(_message);
	}
}

void Chatbox::pushMessage(std::string newMessage)
{
	for (int i = 0; i < CHATBOX_SIZE; ++i)
	{
		if (i == CHATBOX_SIZE - 1)
		{
			if (newMessage == "")
			{
				_messageSize = 0;
				_messages[i] = _message;
				_message = _defaultHeroName;
			}
			else
			{
				_messages[i] = newMessage;
			}
		}
		else
		{
			_messages[i] = _messages[i + 1];
		}
		_labelMessages[i]->setString(_messages[i]);
	}

	_labelInputMessage->setString(_message);
}