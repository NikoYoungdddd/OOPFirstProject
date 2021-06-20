#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"cocos2d.h"
#include"Const/Const.h"
#include"Actor/HeroActor.h"
USING_NS_CC;

class Player :public cocos2d::Layer
{
private:
    Player();
public:
    static Player* getInstance();

    virtual bool init();

    Sprite* getPlayer();

    void addHeroClick(const std::string& heroName);

    void update(float dt);

public:
    unsigned int playerHP;
  
    unsigned int enemyHP;

    unsigned int playerGold;
    
    unsigned int playerLevel;
    
    unsigned int playerExp;
    Sprite* myPlayer;
    ProgressTimer* bloodBar;

    std::vector<int>heroOnReady;
    std::vector<Vec2>heroOnReadyPos;

    std::vector<int> heroOnStage;
    
    std::vector<Vec2>heroONStagePos;


    //"Blood:20 heroNumb:5 heroonready: 1,3,3,2,3   herovec: 1,2 2,3 "
    unsigned int heroOnReadyNum = 0;
    
    unsigned int heroOnStageNum = 0;


private:
    static Player* sharedPlayer;

};
#endif

