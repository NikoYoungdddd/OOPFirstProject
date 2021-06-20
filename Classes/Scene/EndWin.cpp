#include "EndWin.h"
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

Scene* EndWin::createScene()
{
    return EndWin::create();
}

bool EndWin::init()
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
    if (Player::getInstance()->playerHP > 0 && Player::getInstance()->enemyHP == 0)
    {
        auto sprite = Sprite::create(ENDGAME_WIN_WINDOW);
        if (sprite == nullptr)
        {
            problemLoading("'windows/endWinWindow.png'");
        }
        else
        {
            sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(sprite, 1);
        }
    }
    else if (Player::getInstance()->playerHP == 0 && Player::getInstance()->enemyHP > 0)
    {
        auto sprite = Sprite::create(ENDGAME_LOSE_WINDOW);
        if (sprite == nullptr)
        {
            problemLoading("'windows/endLoseWindow.png'");
        }
        else
        {
            sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(sprite, 1);
        }
    }
    else
    {
        auto sprite = Sprite::create(ENDGAME_DRAW_WINDOW);
        if (sprite == nullptr)
        {
            problemLoading("'windows/endDrawWindow.png'");
        }
        else
        {
            sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(sprite, 1);
        }
    }

    //��������
    auto ExitItem = MenuItemImage::create(
        ENDGAME_BUTTON,
        ENDGAME_BUTTON,
        CC_CALLBACK_1(EndWin::menuExit, this));
    if (ExitItem == nullptr ||
        ExitItem->getContentSize().width <= 0 ||
        ExitItem->getContentSize().height <= 0)
    {
        problemLoading("'button/endItem.png'");
    }
    else
    {
        float x = visibleSize.width / 2;
        float y = visibleSize.height / 3 + 49;
        ExitItem->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(ExitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}


void EndWin::menuExit(Ref* pSender)
{
    Director::getInstance()->end();
}