#ifndef __CHAT_LAYER_H__
#define __CHAT_LAYER_H__

#include "Const/Const.h"
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
	
	//发送信息函数 利用editbox 获取当前文本框内信息 发送过后清空
	void sendMessage();
	
	// 在update函数里面执行打印操作
	void update(float ft);
	
	Label* tip;
};
#endif
