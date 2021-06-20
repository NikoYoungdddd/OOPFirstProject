#include "PurchaseScene.h"
extern Player player;
/*图层：（addchild第二个参数）
* 0.map
* 1.按钮
* 2.文字,购买背景
* 3.HeroPurchase图层
*/
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
    auto unclearMap = Sprite::create(PURCHASE_BGMAP);
    if (unclearMap == nullptr)
    {
        problemLoading("'purchaseSceneMap.png'");
    }
    else
    {
        unclearMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(unclearMap, 0);
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

    auto menu = Menu::create(PurchaseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF(PURCHASE, "fonts/Marker Felt.ttf", 28);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 2);
    }
    auto sprite = Sprite::create(PURCHASE_BACKGROUND);
    if (sprite == nullptr)
    {
        problemLoading("'purchaseBg.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 2);
    }
    //添加内容
    auto tip = Label::createWithTTF("the coins you own :", "fonts/Marker Felt.ttf", 28);
    labelPlayerGold = Label::createWithTTF(StringUtils::format("%d", Player::getInstance()->playerGold), "fonts/Marker Felt.ttf", 28);
    if (label == nullptr|| labelPlayerGold ==nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        tip->setPosition(visibleSize.width / 2 - 98 * 3,
            visibleSize.height / 2 + 98 * 2);
        labelPlayerGold->setPosition(visibleSize.width / 2 - 98 * 3+tip->getContentSize().width,
            visibleSize.height / 2 + 98 * 2);
        this->addChild(tip, 2);
        this->addChild(labelPlayerGold, 2);
    }

    HeroPurchase* h = HeroPurchase::create();//修改过 
    this->addChild(h,3);//changed by zhangyu
    this->scheduleUpdate();
    return true;
}

void PurchaseScene::menuReturn(Ref* pSender)
{
    Director::getInstance()->popScene();
}
void PurchaseScene::update(float dt)
{
    if (num == 0)
    {
        auto type = Player::getInstance()->heroOnReady;

        for (unsigned int i = 0; i < type.size() - num; i++)
        {
            //int t = *(type.end() - i - 1);
            int t = *(type.begin() + i);
            auto sprite = Sprite::create(heroPic[t]);
            sprite->setPosition(Vec2(98 * 1.5f, 98.f * ((8 - num - i) + 0.5f)));
            this->addChild(sprite);
        }
        num = Player::getInstance()->heroOnReadyNum;
    }
    else if (Player::getInstance()->heroOnReadyNum > num)
    {

        auto type = Player::getInstance()->heroOnReady;
        for (unsigned int i = 0; i < type.size() - num; i++)
        {

            int t = *(type.end() - i - 1);
            auto sprite = Sprite::create(heroPic[t]);
            sprite->setPosition(Vec2(98 * 1.5f, 98.f * ((8 - num - i) + 0.5f)));
            //此处改变了一下位置
            this->addChild(sprite);
        }
        num = Player::getInstance()->heroOnReadyNum;
    }
    else
    {
        ;
    }
    labelPlayerGold->setString(StringUtils::format("%d", Player::getInstance()->playerGold));
}
