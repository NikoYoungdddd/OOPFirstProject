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

    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuReturn(Ref* pSender);
    CREATE_FUNC(PurchaseScene);

};
#endif
