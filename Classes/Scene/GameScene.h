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

/*��Ϸ������*/
class GameScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
    
    //�رհ�ť�ص����� 
    void menuCloseCallback(Ref* pSender);
   
    //����ť�ص����� 
    void menuToPurchaseLayer(Ref* pSender);
   
    //��֡���º��� 
    void update(float dt);
   
    //�ı����ֵĲ���״̬ 
    void changMusicPlayEvent();
   
    //��ʾ���յ�ʤ����ʧ�ܻ�ƽ�� 
    void EndToWin(float dt);
    
    //���߳� 
    void ThreadRecv();

public:
    unsigned int num;
    HeroLayer* heroLayer;
    Menu* menuUnable;//һ�����Ա������Ĳ˵�����Ϸ�б��������޷����빺����棩 

};

#endif