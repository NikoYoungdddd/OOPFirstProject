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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto chatFrame = Sprite::create(CHAT_BG);
    chatFrame->setPosition(visibleSize.width - chatFrame->getContentSize().width / 2, visibleSize.height - 98 - chatFrame->getContentSize().height / 2);
    this->addChild(chatFrame);
    
    auto editbox1 = ui::EditBox::create(Size(230, 35), ui::Scale9Sprite::create(CHAT_FR));
    editbox1->setAnchorPoint(Point(0, 0));
    editbox1->setPosition(Vec2(visibleSize.width - editbox1->getContentSize().width-40 , visibleSize.height - chatFrame->getContentSize().height-90));
    editbox1->setPlaceHolder("input:");//占位字符
    editbox1->setMaxLength(8);
    editbox1->setFontColor(Color3B::BLACK);//设置输入字体的颜色
    editbox1->setTag(1);
    this->addChild(editbox1, 1);
   
   

    auto sendItem = ui::Button::create(SEND_BUTTON, SEND_BUTTON);
    if (sendItem == nullptr)
    {
        problemLoading("button/chatSendItem.png");
    }
    else
    {
        sendItem->setPosition(Vec2(visibleSize.width - sendItem->getContentSize().width / 2,
            98 * 10 - chatFrame->getContentSize().height - sendItem->getContentSize().height / 2));
        sendItem->addClickEventListener([&](Ref*) 
            { 
               sendMessage();  
            });
        this->addChild(sendItem, 1);
    }
    this->scheduleUpdate();
    return true;
}
void ChatLayer::sendMessage()
{
    auto editbox2 = (ui::EditBox*)this->getChildByTag(1);
    log(editbox2->getText());
    std::string message = editbox2->getText();
    message = "mes" + message;
    if (Player::getInstance()->server == SERVER)
        Server::getInstance()->SendData(message, sizeof(message));
    if (Player::getInstance()->server == CLIENT)
        Client::getInstance()->SendData(message, sizeof(message));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    std::string myMessage = message;
    myMessage.erase(myMessage.begin(), myMessage.begin() + 3);
    auto tip = Label::createWithTTF(myMessage, "fonts/Marker Felt.ttf", 28);
    tip->setPosition(visibleSize.width - 98 * 3 + 35, visibleSize.height - 98 * 2 + 20);
    this->addChild(tip, 1);

    editbox2->setText("");
}

void ChatLayer::update(float ft)
{
   
    /*
    if (Player::getInstance()->server == SERVER)
    {
        if (Server::getInstance()->isMessageDisplayed == false)
        {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            std::string myMessage = Server::getInstance()->getMessage();
            myMessage.erase(myMessage.begin(), myMessage.begin() + 3);

            auto tip = Label::createWithTTF(myMessage, "fonts/Marker Felt.ttf", 28);
             tip->setPosition(visibleSize.width - 98 * 3 + 35, visibleSize.height - 98 * 2 + 20);
            this->addChild(tip, 1);
            

        }

    }
        
    if (Player::getInstance()->server == CLIENT)
        Client::getInstance()->SendData(message, sizeof(message));
        
    ;
    */
    
}