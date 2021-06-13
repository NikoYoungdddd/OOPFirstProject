#include "Scene/PauseScene.h"
#include "Scene/StartGame.h"
#include "Const/Const.h"
USING_NS_CC;
extern int  BGM_name;
extern bool if_bgm_on;
extern bool gIsEffectPlaying;
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}
Scene* PauseScene::createScene()
{
    return PauseScene::create();
}
bool PauseScene::init()
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

    auto ReturnItem = MenuItemImage::create(
        CHESS_PURCHASE,
        CHESS_PURCHASE,
        CC_CALLBACK_1(PauseScene::menuReturn, this));

    if (ReturnItem == nullptr ||
        ReturnItem->getContentSize().width <= 0 ||
        ReturnItem->getContentSize().height <= 0)
    {
        problemLoading("'ChessSelected.png' and 'ChessSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - ReturnItem->getContentSize().width / 2;
        float y = origin.y + ReturnItem->getContentSize().height / 2;
        ReturnItem->setPosition(Vec2(x, y));
    }
    auto MusicItem = MenuItemImage::create(
        CHESS_PURCHASE,
        CHESS_PURCHASE,
        CC_CALLBACK_1(PauseScene::menuReturn, this));

    if (MusicItem == nullptr ||
        MusicItem->getContentSize().width <= 0 ||
        MusicItem->getContentSize().height <= 0)
    {
        problemLoading("'ChessSelected.png' and 'ChessSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - MusicItem->getContentSize().width / 2;
        float y = origin.y + MusicItem->getContentSize().height / 2;
        MusicItem->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(ReturnItem, MusicItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF("Pause!", "fonts/Marker Felt.ttf", 24);
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
    auto sprite = Sprite::create("purchaseBg.png");//换图片
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

    return true;
}
void PauseScene::menuReturn(Ref* pSender)
{
    Director::getInstance()->popScene();
}
void PauseScene::changMusicPlayEvent() {

    if (if_bgm_on) {
        if_bgm_on = false;
        this->getChildByTag(77)->setColor(Color3B(20, 20, 20));
        AudioEngine::pause(BGM_name);
    }
    else
    {
        if_bgm_on = true;
        this->getChildByTag(77)->setColor(Color3B(240, 240, 240));
        AudioEngine::resume(BGM_name);
    }
}