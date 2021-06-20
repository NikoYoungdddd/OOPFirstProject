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

	//��������ɾ��Ԫ��
	template<class T>
	void removeFromVec(const T& pos, std::vector<T>& posVec);

	//����Ӣ�ۣ����� ������  ������x  ������y   ���Ƿ�Ϊ�ҷ����� false�����ҷ�����
	void createHero(const int type, const int x, const int y, bool isAI);

	void createHeroOnReady(const int type);
	void createHeroOnBoard(HeroActor* hero, const int x, const int y);

	//��������
	void testCreate(float dt);
	//�������ҷ���ͬ������Ӣ��
	void testAI(float dt);
	//��һֱ��
	void allocateMyHero();  //�ҷ�����
	void allocateAIHero();  //δ���ҷ����������ӿ����ƶ�
	//����λ������
	void updateHeroPos(bool isAI);

	//��ʼ�µĻغ�
	void startRound(float dt);

	//��ʱ����
	void searchAgain(std::vector<HeroActor*>&vecHero,const std::vector<Vec2>& vecPos,const int side);

	//�ص�ÿ�ֿ�ʼ��λ��
	void boardReset(float dt);
	//��ʵ�֣���ϵ�����������ʱ����
	void timeCountDown(float dt);


	void updateEquipment();

	void updateHeros();

	void createEquipment(const Vec2& pos);


	//Ŀǰ֧��
	//3-4����׼��λ��
	//1�������̣�2��׼��
	//2�������̣�1����׼��
	void heroStarsUP();
	
public:
	std::pair<Vec2, int> board[8][8];
	std::pair<Vec2, int> readyPos[8];
	std::pair<Vec2, int> equipmentPos[8];
	bool isUpdate = false;  //����Ѫ��
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

