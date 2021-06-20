#ifndef __CHOOSE_SCENE_H__
#define __CHOOSE_SCENE_H__


#include "Const/Const.h"
#include "GameScene.h"

/*ѡ����ϷģʽΪ������AI��ս*/
class ChooseScene : public Scene
{

public:
	static Scene* createScene();
	
	virtual bool init();
	
	//ѡ��AI��ս 
	void menuAI(Ref* pSender);
	
	//ѡ��������ս������Ϊ������ 
	void menuServer(Ref* pSender);
	
	//ѡ��������ս�����뷿�䣩 
	void menuClient(Ref* pSender);
	
	CREATE_FUNC(ChooseScene);
};
#endif
