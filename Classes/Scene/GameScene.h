#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Const/Const.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "Layer/Player.h"
#include "Layer/HeroLayer.h"
#include "Layer/ChatLayer.h"
#include "EndScene.h"
#include "ExitScene.h"
#include "PurchaseScene.h"
#include "Net/Server.h"
#include "Net/Client.h"

/*游戏主界面*/
class GameScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
    
    //关闭按钮回调函数 
    void menuCloseCallback(Ref* pSender);
   
    //购买按钮回调函数 
    void menuToPurchaseLayer(Ref* pSender);
   
    //逐帧更新函数 
    void update(float dt);
   
    //改变音乐的播放状态 
    void changMusicPlayEvent();
   
    //显示最终的胜利或失败或平局 
    void EndToWin(float dt);
    
    //多线程 
    void ThreadRecv();

public:
    unsigned int num;
    HeroLayer* heroLayer;
    Menu* menuUnable;//一个可以被锁死的菜单（游戏中被锁死，无法进入购买界面） 

};

#endif