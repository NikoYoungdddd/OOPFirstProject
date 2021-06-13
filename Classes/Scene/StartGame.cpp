#include "Scene/StartGame.h"
#include "Scene/PurchaseScene.h"
//#include "Scene/PauseScene.h"
#include "ui/CocosGUI.h"
#include "Const/Const.h"
using namespace cocos2d::ui;
USING_NS_CC;
Scene* StartGame::createScene()
{
    auto scene = Scene::create();
    auto layer = StartGame::create();
    scene->addChild(layer);
    return scene;
    // return HelloWorld::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool StartGame::init()
{
    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initWithPhysics())
    {
        return false;
    }//changed by zhangyu
    auto visibleSize = Director::getInstance()->getVisibleSize();//这句张宇没有?
    auto winSize = Director::getInstance()->getWinSize();//changed by zhangyu
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        CLOSE_BUTTON,
        CLOSE_BUTTON,
        CC_CALLBACK_1(StartGame::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'closeItem.png' and 'closeItem.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }
    auto PurchaseItem = MenuItemImage::create(
        CHESS_PURCHASE,
        CHESS_PURCHASE,
        CC_CALLBACK_1(StartGame::menuToPurchaseLayer, this));

    if (PurchaseItem == nullptr ||
        PurchaseItem->getContentSize().width <= 0 ||
        PurchaseItem->getContentSize().height <= 0)
    {
        problemLoading("'ChessSelected.png' and 'ChessSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - PurchaseItem->getContentSize().width / 2;
        float y = origin.y + PurchaseItem->getContentSize().height / 2;
        PurchaseItem->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(closeItem, PurchaseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF(TITLE, "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    auto map = TMXTiledMap::create(MAP);
    map->setPosition(0, 0);
    this->addChild(map);
    //添加内容
   // HeroLayer* hh = HeroLayer::create();
  //  this->addChild(hh);//changed by zhangyu
    //auto setItem = Button::create(CHESS_PURCHASE,
    //   CHESS_PURCHASE);//此处还没写完

    return true;
}
void StartGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
void StartGame::menuToPurchaseLayer(Ref* pSender)
{
    Director::getInstance()->pushScene(PurchaseScene::createScene());
}
//void StartGame::menuToPause(Ref* pSender)
//{
//    Director::getInstance()->pushScene(PauseScene::createScene());
//}