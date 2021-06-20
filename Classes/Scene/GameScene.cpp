#include "GameScene.h"

Scene* GameScene::createScene()
{
    return GameScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();//这句张宇没有?
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
        CLOSE_BUTTON,
        CLOSE_BUTTON,
        CC_CALLBACK_1(GameScene::menuCloseCallback, this));

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
        CC_CALLBACK_1(GameScene::menuToPurchaseLayer, this));

    if (PurchaseItem == nullptr ||
        PurchaseItem->getContentSize().width <= 0 ||
        PurchaseItem->getContentSize().height <= 0)
    {
        problemLoading("'ChessSelected.png' and 'ChessSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - PurchaseItem->getContentSize().width / 2;
        float y = origin.y + PurchaseItem->getContentSize().height / 2 + 98 * 3;
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
    auto map = TMXTiledMap::create("chessboard3.tmx");
    this->addChild(map);

    auto player = Player::getInstance();
    this->addChild(player);

    heroLayer = HeroLayer::create();
    this->addChild(heroLayer);  
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt)
{
	if (Player::getInstance()->heroOnReadyNum > num)
	{
		auto heroType = Player::getInstance()->heroOnReady;
		for (unsigned int i = 0; i < heroType.size() - num; i++)
		{     
			int type = *(heroType.end() - i - 1);
            heroLayer->createHeroOnReady(type);
		}
		num = Player::getInstance()->heroOnReadyNum;
	}


}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void GameScene::menuToPurchaseLayer(Ref* pSender)
{
    Director::getInstance()->pushScene(PurchaseScene::createScene());
}