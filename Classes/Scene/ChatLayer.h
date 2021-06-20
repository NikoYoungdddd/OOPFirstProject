#ifndef __CHAT_LAYER_H__
#define __CHAT_LAYER_H__
#include"Const/Const.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class ChatLayer :public cocos2d::Layer
{
public:
	static ChatLayer* create();
	virtual bool init();
	void sendMessage();
};
#endif