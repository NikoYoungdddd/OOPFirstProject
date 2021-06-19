#ifndef __CHAT_LAYER_H__
#define __CHAT_LAYER_H__
#include"Const/Const.h"
#include "ui/CocosGUI.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "Player.h"
#include "Net/Server.h"
#include "Net/Client.h"


USING_NS_CC;
class ChatLayer :public cocos2d::Layer
{
public:
	static ChatLayer* create();
	virtual bool init();
	void sendMessage();
	void update(float ft);
};
#endif
