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
    void playerUpgrade();
    void update(float dt);

public:
    unsigned int playerHP;
    unsigned int playerGold;//表示现有金币（数量）
    Sprite* myPlayer;
    ProgressTimer* bloodBar;
    Label* labelPlayerGold;//表示现有金币的显示（文字）
    std::vector<int>heroOnReady;
    std::vector<Vec2>heroOnReadyPos;
    std::vector<int> heroOnStage;
    std::vector<Vec2>heroONStagePos;
    unsigned int heroOnReadyNum = 0;
    unsigned int heroOnStageNum = 0;


private:
    static Player* sharedPlayer;

};
#endif

