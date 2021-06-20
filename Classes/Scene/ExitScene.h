#ifndef __EXIT_SCENE_H__
#define __EXIT_SCENE_H__

#include "Const/Const.h"

class ExitScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuReturn(Ref* pSender);
    void menuExit(Ref* pSender);
    CREATE_FUNC(ExitScene);
};
#endif
