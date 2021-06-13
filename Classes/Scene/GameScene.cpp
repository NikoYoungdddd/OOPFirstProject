#include "GameScene.h"
#include "HeroLayer.h"

Scene* GameScene::createScene()
{
    return GameScene::create();
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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto map = TMXTiledMap::create("chessboard3.tmx");
    this->addChild(map);

    HeroLayer* hh = HeroLayer::create();
    this->addChild(hh);

    return true;
}
