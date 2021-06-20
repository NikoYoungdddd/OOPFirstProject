#ifndef __CHOOSE_SCENE_H__
#define __CHOOSE_SCENE_H__


#include "Const/Const.h"
#include "GameScene.h"

/*选择游戏模式为联机或AI对战*/
class ChooseScene : public Scene
{

public:
	static Scene* createScene();
	
	virtual bool init();
	
	//选择AI对战 
	void menuAI(Ref* pSender);
	
	//选择联机对战（本人为房主） 
	void menuServer(Ref* pSender);
	
	//选择联机对战（加入房间） 
	void menuClient(Ref* pSender);
	
	CREATE_FUNC(ChooseScene);
};
#endif
