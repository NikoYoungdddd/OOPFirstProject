#ifndef __PURCHASE_SCENE_H__
#define __PURCHASE_SCENE_H__

#include "Const/Const.h"
#include "Layer/Player.h"
#include "Layer/HeroLayer.h"

/*�������ӵĽ���*/
class PurchaseScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    //����׼��ʱ�� 
    void countDownPrepareTime(float dt);
    
    //�ص���Ϸ������ 
    void menuReturn(Ref* pSender);
    
    //��֡���º��� 
    void update(float dt);

    CREATE_FUNC(PurchaseScene);


private:
    unsigned int num;
    //��ʾ���н�ҵ����� 
    Label* labelPlayerGold;
    //��ʾ���ڵ���ʱ������ 
    Label* labelPrepareTime;
};
#endif