#ifndef __EXIT_SCENE_H__
#define __EXIT_SCENE_H__

#include "Const/Const.h"

/*�˳�����*/
class ExitScene : public Scene
{

public:
    static Scene* createScene();

    virtual bool init();
   
    //����˳��ص���Ϸ 
    void menuReturn(Ref* pSender);
   
    //ȷ���˳� 
    void menuExit(Ref* pSender);
   
    CREATE_FUNC(ExitScene);
};
#endif
