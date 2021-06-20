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

	//����Ӣ�ۣ����� ������  ������x  ������y   ���Ƿ�Ϊ�ҷ����� false�����ҷ�����
	void createHero(const int type, const int x, const int y, bool isAI, const int star = 1);
	
	void createHeroOnReady(const int type);
	
	void createHeroOnBoard(HeroActor* hero, const int x, const int y);
	
	//AI����
	void AIHeroCreateStarsUP();
	
	void createAIHeros(float dt);

	//ÿ�ֽ����ָ�����
	void boardReset(float dt);
	
	//��ʼ�µ�һ�֣�������������allocate
	void startRound(float dt);
	
	void allocateMyHero();  //�ҷ�����
	
	void allocateAIHero();  //δ���ҷ����������ӿ����ƶ�

	//����װ��
	void createEquipment();
	

	//update����
	void updateEquipment();
	
	void AIHeroStarsUP();
	
	void updateHeroPos(bool isAI);
	
	void updateHeros();

	//Ŀǰ֧��
	//3-4����׼��λ��
	//1�������̣�2��׼��
	//2�������̣�1����׼��
	void heroStarsUP();
	
	void update(float ft);


	//����ʱ���պʹ���
	void sendMyHeros(float dt);
	
	void recvSend(float dt);

	//���ܼ��ϵ�
	//��ʵ�֣���ϵ�����������ʱ����
	void timeCountDown(float dt);
	
	//����ʱ
	void showResultPerTime(int ifWin);
	
	void countDownBattleTime(float dt);
	
	void countDownPrepareTime(float dt);
	
	void eraseLablePrepareTime();
	
	void HeroLayer::addLablePrepareTime();

	//�¼�����
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_even);
	
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//��������ɾ��Ԫ��
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
	std::vector<Vec2> vecAIHeroPos;  //�з�λ��
	std::vector<Vec2> vecMyHeroPos;  //�ҷ�λ��
	std::vector<HeroActor*> vecMyHeros;  //�ҷ�
	std::vector<HeroActor*> vecAIHeros;  //�з�	
	int numMyHeros = 0;
	int numAIHeros = 0;

	//����reset��
	std::vector<Vec2>vecMyHeroReset;  //����ÿ�ֿ�ʼǰ��λ��
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


