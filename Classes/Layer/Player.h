#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"cocos2d.h"
#include"Const/Const.h"
#include"Actor/HeroActor.h"

class Player :public Layer
{
private:
    Player();
public:
    static Player* getInstance();

    virtual bool init();

    Sprite* getPlayer();

    //��ȡ�����Ӣ��
    void addHeroClick(const std::string& heroName);
    
    //����
    void playerUpgrade();

    void update(float dt);

public:
   
    unsigned int playerHP;
    unsigned int playerGold;//��ʾ���н�ң�������
    Sprite* myPlayer;
    ProgressTimer* bloodBar;
    ProgressTimer* AIbloodBar;
    ProgressTimer* ExpBar;
    Label* labelPlayerGold;//��ʾ���н�ҵ���ʾ�����֣�
    Label* labelPlayerGrade;//��ʾ���еȼ�����ʾ�����֣�
    Label* labelPlayerHP;//��ʾ����Ѫ������ʾ�����֣�
    Label* labelAIHP;//��ʾ����Ѫ������ʾ�����֣�
    Label* labelPlayerExp;//��ʾ���о���ֵ����ʾ�����֣�
    std::vector<int>heroOnReady;
 
    unsigned int heroOnReadyNum = 0;
    unsigned int heroOnStageNum = 0;
    unsigned int enemyHP;
    int playerExp;
    int playerGrade;
    //���ϵ�
    float downPrepareTime;
    bool isRoundEnd = false;
    //0619�������
    bool isAI;
    int server;

private:
    static Player* sharedPlayer;

};
#endif


