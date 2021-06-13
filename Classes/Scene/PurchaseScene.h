#ifndef __PURCHASE_SCENE_H__
#define __PURCHASE_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class PurchaseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuReturn(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(PurchaseScene);
    TMXTiledMap* chessboard3;
};
#endif
