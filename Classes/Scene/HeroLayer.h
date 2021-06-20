#ifndef __HERO_LAYER_H__
#define __HERO_LAYER_H__

#include "Actor/Assasion.h"
#include "Actor/Tank.h"
#include "Actor/ADC.h"
#include "Actor/AOE.h"
#include "Actor/AP.h"
#include "HeroPurchase.h"
#include "Item/Equipment.h"


#define AI_SIDE 0
#define MY_SIDE 1

class HeroLayer :public Layer
{
public:
	HeroLayer();

	virtual bool init();

	static HeroLayer* create();

	void update(float ft);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_even);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//从容器中删除元素
	template<class T>
	void removeFromVec(const T& pos, std::vector<T>& posVec);

	//创建英雄，参数 ：种类  、棋盘x  、棋盘y   、是否为我方创建 false是是我方创建
	void createHero(const int type, const int x, const int y, bool isAI);

	void createHeroOnReady(const int type);
	void createHeroOnBoard(HeroActor* hero, const int x, const int y);

	//仅测试用
	void testCreate(float dt);
	//产生与我方相同个数的英雄
	void testAI(float dt);
	//可一直用
	void allocateMyHero();  //我方先手
	void allocateAIHero();  //未被我方锁定的棋子可以移动
	//更新位置容器
	void updateHeroPos(bool isAI);

	//开始新的回合
	void startRound(float dt);

	//暂时无用
	void searchAgain(std::vector<HeroActor*>&vecHero,const std::vector<Vec2>& vecPos,const int side);

	//回到每局开始的位置
	void boardReset(float dt);
	//空实现，配合调度器产生延时作用
	void timeCountDown(float dt);


	void updateEquipment();

	void updateHeros();

	void createEquipment(const Vec2& pos);


	//目前支持
	//3-4个在准备位置
	//1个在棋盘，2个准备
	//2个在棋盘，1个在准备
	void heroStarsUP();
	
public:
	std::pair<Vec2, int> board[8][8];
	std::pair<Vec2, int> readyPos[8];
	std::pair<Vec2, int> equipmentPos[8];
	bool isUpdate = false;  //更新血条
	float deltaX;
	float deltaY;
	std::vector<HeroActor*>vecHeroOnReady;
	//std::vector<HeroActor*>vecHeroOnBoard;

	int arrayHeroNum[5]={};

	bool isStartNewRound = false;
	bool isGameStart = false;
	
	unsigned int AIGold = 4;
	unsigned int AIExp = 0;
	unsigned int AILevel = 1;
private:
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

	//Test Equipment
	
	std::vector<Equipment*>vecEquipmentUncollected;
	std::vector<Sprite*>vecEquipment;
	std::vector<std::string>vecEquipmentName;
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

