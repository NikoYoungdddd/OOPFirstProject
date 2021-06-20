#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Const/Const.h"
#include "Player.h"
#include "HeroLayer.h"
#include "PurchaseScene.h"
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuToPurchaseLayer(Ref* pSender);
    void update(float dt);

public:
    unsigned int num;

    HeroLayer* heroLayer;
};

#endif // __HELLOWORLD_SCENE_H__