#ifndef __START_GAME_H__
#define __START_GAME_H__
#include "cocos2d.h"
USING_NS_CC;
class StartGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuToPurchaseLayer(Ref* pSender);
    // void menuToPause(Ref* pSender);
     // implement the "static create()" method manually
     //void menuCallback(cocos2d::Ref* pSender);
      //bool onContactBegin(cocos2d::PhysicsContact& contact);
    CREATE_FUNC(StartGame);
    TMXTiledMap* chessboard3;
};
#endif
