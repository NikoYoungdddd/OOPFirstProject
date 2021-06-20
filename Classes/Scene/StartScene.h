#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "Const/Const.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ChooseScene.h"
#include "ExitScene.h"

/*��Ϸ�Ŀ�ʼ����*/
class StartScene : public Scene
{

public:
    static Scene* createScene();

    virtual bool init();
    
    //��ʼ������İ�ť��Ӧ�ص����� 
    void StartCallback(cocos2d::Ref* pSender);
    
    void CloseCallback(Ref* pSender);
    
    //�ı����ֲ���״̬ 
    void changMusicPlayEvent();
   
    CREATE_FUNC(StartScene);
};
#endif