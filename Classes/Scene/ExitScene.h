#ifndef __EXIT_SCENE_H__
#define __EXIT_SCENE_H__

#include "Const/Const.h"

/*退出界面*/
class ExitScene : public Scene
{

public:
    static Scene* createScene();

    virtual bool init();
   
    //误点退出回到游戏 
    void menuReturn(Ref* pSender);
   
    //确定退出 
    void menuExit(Ref* pSender);
   
    CREATE_FUNC(ExitScene);
};
#endif
