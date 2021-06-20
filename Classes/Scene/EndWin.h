#ifndef __END_WIN_H__
#define __END_WIN_H__
#include "cocos2d.h"
#include "Const/Const.h"
#include "Player.h"
USING_NS_CC;
class EndWin : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuExit(Ref* pSender);
	CREATE_FUNC(EndWin);
};
#endif