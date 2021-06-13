#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__
#include "cocos2d.h"
#include "AudioEngine.h"
USING_NS_CC;
class PauseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuMusic(Ref* pSender);
    void menuReturn(Ref* pSender);
private:
    /* 改变音效播放状态*/
    //void changEffectPlayEvent();

     /* 改变音乐播放状态*/
    void changMusicPlayEvent();

    /* 按按钮的时候当然要放音效*/
    static void playClickEffect();
};
#endif