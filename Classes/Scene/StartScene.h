#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "Const/Const.h"
#include "AudioEngine.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void StartCallback(cocos2d::Ref* pSender);
    void CloseCallback(Ref* pSender);
    void changMusicPlayEvent();
    CREATE_FUNC(StartScene);
};
#endif
