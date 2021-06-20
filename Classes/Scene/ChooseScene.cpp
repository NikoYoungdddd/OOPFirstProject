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

    return true;
}
void ChooseScene::menuAI(Ref* pSender)
{
    Player::getInstance()->isAI = 1;
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void ChooseScene::menuServer(Ref* pSender)
{
    Player::getInstance()->isAI = 0;
    Player::getInstance()->server = isServer;
    Director::getInstance()->replaceScene(GameScene::createScene());
}
void ChooseScene::menuClient(Ref* pSender)
{
    Player::getInstance()->isAI = 0;
    Player::getInstance()->server = isClient;
    Director::getInstance()->replaceScene(GameScene::createScene());
}
