#include "Scene/StartScene.h"
#include "Scene/StartGame.h"
#include "Const/Const.h"
//#include "ui/CocosGUI.h"
//using namespace cocos2d::ui;
USING_NS_CC;
//#define BGM "music/bgm_1.mp3"
//#define BGM_pressed "music/pressed.mp3"
//#define BGM_game "music/bgm_game.mp3"
int  BGM_name;
bool if_bgm_on = 1;
bool gIsEffectPlaying = 1;
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}
Scene* StartScene::createScene()
{
    return StartScene::create();
}
bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    BGM_name = AudioEngine::play2d(BGM, true, .5);
    AudioEngine::preload(BGM_pressed);
    if_bgm_on = true;
    gIsEffectPlaying = true;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        CLOSE_BUTTON,
        CLOSE_BUTTON,
        CC_CALLBACK_1(StartScene::CloseCallback, this));
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
    auto startItem = MenuItemImage::create(
        START_BUTTON,
        START_BUTTON,
        CC_CALLBACK_1(StartScene::StartCallback, this));
    if (startItem == nullptr ||
        startItem->getContentSize().width <= 0 ||
        startItem->getContentSize().height <= 0)
    {
        problemLoading("'startItem.png' and 'startItem.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - startItem->getContentSize().width / 2;
        float y = origin.y + startItem->getContentSize().height / 2 + 98 * 3;
        startItem->setPosition(Vec2(x, y));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF(TITLE, "fonts/Marker Felt.ttf", 24);

    auto sprite = Sprite::create(START_BACKGROUND);
    if (sprite == nullptr)
    {
        problemLoading("'startBg.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    }
    return true;
}
void StartScene::CloseCallback(Ref* pSender)
{

    Director::getInstance()->end();
}
void StartScene::StartCallback(Ref* pSender)
{
    AudioEngine::pause(BGM_name);

    BGM_name = AudioEngine::play2d(BGM_game, true, 0.5f);
    if (!if_bgm_on)
        AudioEngine::pause(BGM_name);
    Director::getInstance()->replaceScene(TransitionMoveInB::create(1.0f, StartGame::createScene()));
}