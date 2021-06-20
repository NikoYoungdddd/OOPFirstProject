#ifndef __CHOOSE_SCENE_H__
#define __CHOOSE_SCENE_H__
#include "GameScene.h"
#include "Const/Const.h"
USING_NS_CC;
class ChooseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuAI(Ref* pSender);
	void menuServer(Ref* pSender);
	void menuClient(Ref* pSender);
	CREATE_FUNC(ChooseScene);
};
#endif

