#ifndef __HERO_LAYER_H__
#define __HERO_LAYER_H__

#include <sstream>
#include "Actor/Assasion.h"
#include "Actor/Tank.h"
#include "Actor/ADC.h"
#include "Actor/AOE.h"
#include "Actor/AP.h"
#include "HeroPurchase.h"
#include "Item/Equipment.h"
#include "AudioEngine.h"
#include "Net/Client.h"
#include "Net/Server.h"

class HeroLayer :public Layer
{
public:

	HeroLayer();

	virtual bool init();

	static HeroLayer* create();

	//创建英雄，参数 ：种类  、棋盘x  、棋盘y   、是否为我方创建 false是是我方创建
	void createHero(const int type, const int x, const int y, bool isAI, const int star = 1);
	
	void createHeroOnReady(const int type);
	
	void createHeroOnBoard(HeroActor* hero, const int x, const int y);
	
	//AI升星
	void AIHeroCreateStarsUP();
	
	void createAIHeros(float dt);

	//每轮结束恢复棋盘
	void boardReset(float dt);
	
	//开始新的一局，调用下面两个allocate
	void startRound(float dt);
	
	void allocateMyHero();  //我方先手
	
	void allocateAIHero();  //未被我方锁定的棋子可以移动

	//创建装备
	void createEquipment();
	

	//update函数
	void updateEquipment();
	
	void AIHeroStarsUP();
	
	void updateHeroPos(bool isAI);
	
	void updateHeros();

	//目前支持
	//3-4个在准备位置
	//1个在棋盘，2个准备
	//2个在棋盘，1个在准备
	void heroStarsUP();
	
	void update(float ft);


	//联机时接收和传送
	void sendMyHeros(float dt);
	
	void recvSend(float dt);

	//我能加上的
	//空实现，配合调度器产生延时作用
	void timeCountDown(float dt);
	
	//倒计时
	void showResultPerTime(int ifWin);
	
	void countDownBattleTime(float dt);
	
	void countDownPrepareTime(float dt);
	
	void eraseLablePrepareTime();
	
	void HeroLayer::addLablePrepareTime();

	//事件监听
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_even);
	
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//从容器中删除元素
	template<class T>
	void removeFromVec(const T& pos, std::vector<T>& posVec);

public:

	std::string test_pvp;
	std::string s1;

	std::pair<Vec2, int> board[8][8];
	std::pair<Vec2, int> readyPos[8];
	std::pair<Vec2, int> equipmentPos[8];
	int arrayHeroNum[5] = {};
	int arrayAIHeroNum[5] = {};

	bool isUpdate = false;
	bool isStartNewRound = false;
	bool isGameStart = false;
	bool isEnemyEnd = false;

	int AIGold = 3;
	int AIExp = 0;
	int AIGrade = 1;

private:

	//labels
	Label* labelPrepareTime;
	Label* labelBattleTime;
	int downBattleTime = ROUND_TIME;
	int buffNum = 0;
	int bgmBattle;

	//restore my hero
	std::vector<HeroActor*>vecHeroOnReady;
	std::vector<Vec2> vecAIHeroPos;  //敌方位置
	std::vector<Vec2> vecMyHeroPos;  //我方位置
	std::vector<HeroActor*> vecMyHeros;  //我方
	std::vector<HeroActor*> vecAIHeros;  //敌方	
	int numMyHeros = 0;
	int numAIHeros = 0;

	//仅在reset用
	std::vector<Vec2>vecMyHeroReset;  //保存每局开始前的位置
	std::vector<std::pair<int, int>>vecMyHeroBoardPos;
	std::vector<Vec2>vecAIHeroReset;
	std::vector<std::pair<int, int>>vecAIHeroBoardPos;

	//Equipment
	std::vector<Equipment*>vecEquipmentUncollected;
	std::vector<Sprite*>vecEquipment;
	std::vector<std::string>vecEquipmentName;
	
	//Touch
	EventListenerTouchOneByOne* touchListener;
	float deltaX;
	float deltaY;
	Vec2 touchedEquipmentPos;
	Sprite* touchedEquipment;
	std::string touchedEquipmentName;
	unsigned int chosedEquipmentNo = 0;
	bool isEquipmentTouched = false;
	int eqpnum = 0;

	std::vector<Vec2> vec;
	bool isHeroTouched = false;
	Vec2 touchedHeroPos;
	HeroActor* touchedHero;
	unsigned int chosedHeroNo = 0;
};
#endif


