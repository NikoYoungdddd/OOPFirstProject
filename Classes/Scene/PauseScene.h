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
    /* �ı���Ч����״̬*/
    //void changEffectPlayEvent();

     /* �ı����ֲ���״̬*/
    void changMusicPlayEvent();

    /* ����ť��ʱ��ȻҪ����Ч*/
    static void playClickEffect();
};
#endif