#ifndef __PURCHASE_SCENE_H__
#define __PURCHASE_SCENE_H__

#include "Const/Const.h"
#include "Layer/Player.h"
#include "Layer/HeroLayer.h"

/*购买棋子的界面*/
class PurchaseScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    //倒数准备时间 
    void countDownPrepareTime(float dt);
    
    //回到游戏主界面 
    void menuReturn(Ref* pSender);
    
    //逐帧更新函数 
    void update(float dt);

    CREATE_FUNC(PurchaseScene);


private:
    unsigned int num;
    //显示现有金币的文字 
    Label* labelPlayerGold;
    //显示现在倒计时的文字 
    Label* labelPrepareTime;
};
#endif