#ifndef __END_SCENE_H__
#define __END_SCENE_H__

#include "Const/Const.h"
#include "Layer/Player.h"

/*���յ���Ӯ����*/
class EndScene : public Scene
{
public:
	static Scene* createScene();
	
	virtual bool init();
	
	void menuExit(Ref* pSender);
	
	CREATE_FUNC(EndScene);
};
#endif
