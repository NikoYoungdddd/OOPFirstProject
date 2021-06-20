#ifndef __PURCHASE_SCENE_H__
#define __PURCHASE_SCENE_H__

#include "Player.h"
#include "HeroLayer.h"
#include "Const/Const.h"

class PurchaseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuReturn(Ref* pSender);
    void PurchaseScene::update(float dt);
    CREATE_FUNC(PurchaseScene);
private:
    unsigned int num;
    Label* labelPlayerGold;
};
#endif
