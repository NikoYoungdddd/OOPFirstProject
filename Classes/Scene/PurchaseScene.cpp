#include "PurchaseScene.h"
extern bool IfReAddPrepareTime;
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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto unclearMap = Sprite::create(UNCLEAR_MAP);
    if (unclearMap == nullptr)
    {
        problemLoading("'background/unclearMap.png'");
    }
    else
    {
        unclearMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(unclearMap, 0);
    }
    auto PurchaseItem = MenuItemImage::create(
        CHESS_PURCHASE_BUTTON,
        CHESS_PURCHASE_BUTTON,
        CC_CALLBACK_1(PurchaseScene::menuReturn, this));

    if (PurchaseItem == nullptr ||
        PurchaseItem->getContentSize().width <= 0 ||
        PurchaseItem->getContentSize().height <= 0)
    {
        problemLoading("'button/ChessSelected.png'");
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

    auto sprite = Sprite::create(PURCHASE_BACKGROUND);
    if (sprite == nullptr)
    {
        problemLoading("'background/purchaseBg.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 2);
    }

    auto tip = Label::createWithTTF("the coins you own :", "fonts/Marker Felt.ttf", 28);
    labelPlayerGold = Label::createWithTTF(StringUtils::format("%d", Player::getInstance()->playerGold), 
        "fonts/Marker Felt.ttf", 28);
    if (labelPlayerGold ==nullptr)
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

    HeroPurchase* h = HeroPurchase::create(); 
    this->addChild(h,3);
    labelPrepareTime = Label::createWithTTF(StringUtils::format("In Preparation : %d second",
        static_cast<int>(Player::getInstance()->downPrepareTime) + 1), "fonts/Marker Felt.ttf", 28);
    labelPrepareTime->setPosition(Vec2(visibleSize.width / 2,
        visibleSize.height - labelPrepareTime->getContentSize().height));
    this->addChild(labelPrepareTime);
    schedule(CC_SCHEDULE_SELECTOR(PurchaseScene::countDownPrepareTime), 1.0f/60);

    this->scheduleUpdate();
    return true;
}

void PurchaseScene::menuReturn(Ref* pSender)
{
    IfReAddPrepareTime = 1;
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

void PurchaseScene::countDownPrepareTime(float dt)
{
    Player::getInstance()->downPrepareTime -= 1.0f/60;
    labelPrepareTime->setString(StringUtils::format("In Preparation : %d second", 
        static_cast<int>(Player::getInstance()->downPrepareTime) + 1));
    if (Player::getInstance()->downPrepareTime <= 0)
    {
        unschedule(CC_SCHEDULE_SELECTOR(PurchaseScene::countDownPrepareTime));
        removeChild(labelPrepareTime);
        Player::getInstance()->downPrepareTime = PREPARE_TIME;
    }
}