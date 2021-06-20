#include "StartScene.h"

int BGM_ID;
bool if_bgm_on;
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
   
    BGM_ID=AudioEngine::play2d(BGM, true, .5);
    //AudioEngine::preload(BGM_pressed);
    if_bgm_on = true;

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
        float y = origin.y - closeItem->getContentSize().height / 2+98*10;
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
        float y = origin.y + startItem->getContentSize().height / 2;
        startItem->setPosition(Vec2(x, y));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto MusicBt = Sprite::create(MUSIC_BUTTON_BACKGROUND);
    auto BackGround = Sprite::create(START_BACKGROUND);
    if (MusicBt == nullptr|| BackGround == nullptr)
    {
        problemLoading("'music_button_bg.png'and'startBg.png'");
    }
    else
    {
        BackGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(BackGround, 0);
        float x = origin.x + visibleSize.width - MusicBt->getContentSize().width / 2*3;
        float y = origin.y - MusicBt->getContentSize().height / 2 + 98 * 10;
        MusicBt->setPosition(Vec2(x, y));
        this->addChild(MusicBt, 0);
        //在这里为了避免对于空指针closeItem的引用，将图片素材的音乐按钮背景与关闭图标设置为统一大小
    }
    auto musicItem = ui::Button::create(MUSIC_BUTTON_CONTENT,
        MUSIC_BUTTON_CONTENT);
    if (musicItem == nullptr)
    {
        problemLoading("music_button_content.png");
    }
    else
    {
        if (!if_bgm_on)
            musicItem->setColor(Color3B(20, 20, 20));
        float x = origin.x + visibleSize.width - musicItem->getContentSize().width / 2*3;
        float y = origin.y - musicItem->getContentSize().height / 2+98*10;
        musicItem->setPosition(Vec2(x, y));
        musicItem->addClickEventListener([&](Ref*) { changMusicPlayEvent(); });
        this->addChild(musicItem, 2, 77);
    }
   
    return true;
}
void StartScene::CloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
void StartScene::StartCallback(Ref* pSender)
{
    AudioEngine::pause(BGM_ID);
    //if (if_bgm_on==1)
    //{
    //    BGM_ID = AudioEngine::play2d(BGM_game, true, 0.5f);
    //}
    Director::getInstance()->replaceScene(TransitionMoveInB::create(1.0f, GameScene::createScene()));
}
void StartScene::changMusicPlayEvent() {

    if (if_bgm_on) {
        if_bgm_on = false;
        this->getChildByTag(77)->setColor(Color3B(20, 20, 20));
        AudioEngine::pause(BGM_ID);
    }
    else
    {
        if_bgm_on = true;
        this->getChildByTag(77)->setColor(Color3B(240, 240, 240));
        AudioEngine::resume(BGM_ID);
    }
}