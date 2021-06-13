#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "cocos2d.h"
#include "AudioEngine.h"
//#include "Const/Const.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void StartCallback(cocos2d::Ref* pSender);
    void CloseCallback(Ref* pSender);
    //void SetCallback(Ref* pSender);
    CREATE_FUNC(StartScene);
};
#endif
