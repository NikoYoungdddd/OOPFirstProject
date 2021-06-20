#include "ExitScene.h"

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}


Scene* ExitScene::createScene()
{
    return ExitScene::create();
}


bool ExitScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto unclearMap = Sprite::create(UNCLEAR_MAP);
    if (unclearMap == nullptr)
    {
        problemLoading("'background/unclearMap.png'");
    }
    else
    {
        unclearMap->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(unclearMap, 0);
    }
    auto sprite = Sprite::create(PURCHASE_BACKGROUND);
    if (sprite == nullptr)
    {
        problemLoading("'background/purchaseBg.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        sprite->setColor(Color3B(20, 20, 20));
        this->addChild(sprite, 0);
    }
    //Ìí¼ÓÄÚÈÝ
    auto ReturnItem = MenuItemImage::create(
        RETURN_BUTTON,
        RETURN_BUTTON,
        CC_CALLBACK_1(ExitScene::menuReturn, this));
    if (ReturnItem == nullptr ||
        ReturnItem->getContentSize().width <= 0 ||
        ReturnItem->getContentSize().height <= 0)
    {
        problemLoading("'button/noButton'");
    }
    else
    {
        float x = visibleSize.width / 3;
        float y = visibleSize.height / 3 + 49;
        ReturnItem->setPosition(Vec2(x, y));
    }
    auto ExitItem = MenuItemImage::create(
        EXIT_BUTTON,
        EXIT_BUTTON,
        CC_CALLBACK_1(ExitScene::menuExit, this));
    if (ExitItem == nullptr ||
        ExitItem->getContentSize().width <= 0 ||
        ExitItem->getContentSize().height <= 0)
    {
        problemLoading("'button/yesItem'");
    }
    else
    {
        float x = visibleSize.width / 3 * 2;
        float y = visibleSize.height / 3 + 49;
        ExitItem->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(ReturnItem, ExitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto tip = Label::createWithTTF("Are you sure to exit the game? ", "fonts/Marker Felt.ttf", 40);
    if (tip == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        tip->setPosition(visibleSize.width / 2,
            visibleSize.height / 2 + 98 * 0.5f);
        this->addChild(tip, 2);
    }

    this->scheduleUpdate();
    return true;
}


void ExitScene::menuReturn(Ref* pSender)
{
    Director::getInstance()->popScene();
}


void ExitScene::menuExit(Ref* pSender)
{
    Director::getInstance()->end();
}