#include "PurchaseScene.h"

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

Scene* PurchaseScene::createScene()
{
    return PurchaseScene::create();
}

bool PurchaseScene::init()
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
        CC_CALLBACK_1(PurchaseScene::menuCloseCallback, this));

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
        CC_CALLBACK_1(PurchaseScene::menuReturn, this));

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
    auto sprite = Sprite::create(PURCHASE_BACKGROUND);
    if (sprite == nullptr)
    {
        problemLoading("'purchaseBg.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    }
    //添加内容
    HeroPurchase* h = HeroPurchase::create();
    this->addChild(h);

    return true;
}

void PurchaseScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void PurchaseScene::menuReturn(Ref* pSender)
{
    Director::getInstance()->popScene();
}