#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Const/Const.h"
#include "HeroLayer.h"
#include "PurchaseScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "ChatLayer.h"
#include "ExitScene.h"
#include "EndWin.h"
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
    void menuCloseCallback(Ref* pSender);
    void menuToPurchaseLayer(Ref* pSender);
    void update(float dt);
    void changMusicPlayEvent();
    void EndToWin(float dt);
public:
    unsigned int num;
    HeroLayer* heroLayer;
};

#endif // __HELLOWORLD_SCENE_H__