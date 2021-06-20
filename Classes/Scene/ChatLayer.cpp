#include "ChatLayer.h"

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

ChatLayer* ChatLayer::create()
{
	ChatLayer* pRet = new ChatLayer();

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		if (pRet != nullptr)
		{
			delete pRet;
			pRet = nullptr;
		}
		return nullptr;
	}
}

bool ChatLayer::init()
{
    if (!Layer::init())
    {
        return true;
    } 
    auto visibleSize = Director::getInstance()->getVisibleSize();//这句张宇没有?
    auto winSize = Director::getInstance()->getWinSize();//changed by zhangyu
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto chatFrame = Sprite::create(CHAT_WINDOW);
    chatFrame->setPosition(visibleSize.width- chatFrame->getContentSize().width / 2, visibleSize.height-98- chatFrame->getContentSize().height/2);
    this->addChild(chatFrame);

    auto sendItem = ui::Button::create(SEND_BUTTON, SEND_BUTTON);
    if (sendItem == nullptr)
    {
        problemLoading("upgradeItem.png");
    }
    else
    {
        sendItem->setPosition(Vec2(visibleSize.width- sendItem->getContentSize().width / 2,
            98 * 10- chatFrame->getContentSize().height - sendItem->getContentSize().height / 2));
        sendItem->addClickEventListener([&](Ref*) { sendMessage(); });
        this->addChild(sendItem, 1);
    }
	return true;
}
void ChatLayer::sendMessage()
{
    ;
}