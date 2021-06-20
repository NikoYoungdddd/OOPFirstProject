#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "Const/Const.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ChooseScene.h"
#include "ExitScene.h"

/*游戏的开始界面*/
class StartScene : public Scene
{

public:
    static Scene* createScene();

    virtual bool init();
    
    //开始与结束的按钮对应回调函数 
    void StartCallback(cocos2d::Ref* pSender);
    
    void CloseCallback(Ref* pSender);
    
    //改变音乐播放状态 
    void changMusicPlayEvent();
   
    CREATE_FUNC(StartScene);
};
#endif