#include "ChooseScene.h"

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}


Scene* ChooseScene::createScene()
{
    return ChooseScene::create();
}


bool ChooseScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto unclearBg = Sprite::create(UNCLEAR_BACKGROUND);
    if (unclearBg == nullptr)
    {
        problemLoading("'background/unclearstartBg.png'");
    }
    else
    {
        unclearBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(unclearBg, 0);
    }
    auto AIItem = MenuItemImage::create(
        CHOOSE_AI_BUTTON,
        CHOOSE_AI_BUTTON,
        CC_CALLBACK_1(ChooseScene::menuAI, this));
    if (AIItem == nullptr ||
        AIItem->getContentSize().width <= 0 ||
        AIItem->getContentSize().height <= 0)
    {
        problemLoading("'button/AIItem.png'");
    }
    else
    {
        AIItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 3));
    }
    auto ServerItem = MenuItemImage::create(
        CHOOSE_SERVER_BUTTON,
        CHOOSE_SERVER_BUTTON,
        CC_CALLBACK_1(ChooseScene::menuServer, this));
    if (ServerItem == nullptr ||
        ServerItem->getContentSize().width <= 0 ||
        ServerItem->getContentSize().height <= 0)
    {
        problemLoading("'button/serverItem.png'");
    }
    else
    {
        ServerItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 2));
    }
    auto ClientItem = MenuItemImage::create(
        CHOOSE_CLIENT_BUTTON,
        CHOOSE_CLIENT_BUTTON,
        CC_CALLBACK_1(ChooseScene::menuClient, this));
    if (ClientItem == nullptr ||
        ClientItem->getContentSize().width <= 0 ||
        ClientItem->getContentSize().height <= 0)
    {
        problemLoading("'button/clientItem.png'");
    }
    else
    {
        ClientItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
    }
    auto menu = Menu::create(AIItem, ServerItem, ClientItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto editbox1 = ui::EditBox::create(Size(300, 50), ui::Scale9Sprite::create(CHAT_FR));
    editbox1->setAnchorPoint(Point(0, 0));
    editbox1->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 + 60));
    editbox1->setPlaceHolder("Server ip:");//占位字符
    editbox1->setMaxLength(20);
    editbox1->setFontColor(Color3B::BLACK);//设置输入字体的颜色
    editbox1->setTag(1);

    auto editbox2 = ui::EditBox::create(Size(300, 50), ui::Scale9Sprite::create(CHAT_FR));
    editbox2->setAnchorPoint(Point(0, 0));
    editbox2->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 4 + 60));
    editbox2->setPlaceHolder("Client ip:");//占位字符
    editbox2->setMaxLength(20);
    editbox2->setFontColor(Color3B::BLACK);//设置输入字体的颜色
    editbox2->setTag(2);

    this->addChild(editbox1, 1);
    this->addChild(editbox2, 1);


    return true;
}


void ChooseScene::menuAI(Ref* pSender)
{
    Player::getInstance()->isAI = 1;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
}


void ChooseScene::menuServer(Ref* pSender)
{
    Player::getInstance()->isAI = 0;
    Player::getInstance()->server = SERVER;

    auto editbox3 = (ui::EditBox*)this->getChildByTag(1);
	Server::getInstance()->myIP = editbox3->getText();
	log(editbox3->getText());
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
}


void ChooseScene::menuClient(Ref* pSender)
{
	Player::getInstance()->isAI = 0;
	Player::getInstance()->server = CLIENT;

	auto editbox4 = (ui::EditBox*)this->getChildByTag(2);
	Client::getInstance()->myIP = editbox4->getText();

	log(editbox4->getText());
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
}