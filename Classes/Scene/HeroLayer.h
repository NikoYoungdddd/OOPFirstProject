#ifndef __HERO_LAYER_H__
#define __HERO_LAYER_H__

#include "Actor/Assasion.h"
#include "Actor/Tank.h"
#include "Actor/ADC.h"
#include "Actor/AOE.h"
#include "Actor/AP.h"
#include "HeroPurchase.h"
#include "Item/Equipment.h"

class HeroLayer :public Layer
{
public:
	HeroLayer();

	virtual bool init();

	static HeroLayer* create();

	void update(float ft);

	void createPushActor(const std::string& hero, const Vec2& putPos);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_even);

	bool onContactBegin(cocos2d::PhysicsContact& contact);

	void removeFromPositonVec(const Vec2& pos, std::vector<Vec2>& posVec);

	//仅测试用
	void testCreate();
	void testPush(const int n, const Vec2& pos, const int c);
	void testPosAllocate(float dt);
	void testEnemy(float dt);

public:

	std::pair<Vec2, int> board[8][8];

	float deltaX;
	float deltaY;

	//仅测试用
	bool isTest = false;
	bool isUpdate = false;
private:

	//Test HeroTouch
	std::vector<Vec2> vec;
	bool isHeroTouched = false;
	Vec2 touchedHeroPos;
	HeroActor* touchedHero;
	int chosedHeroNo = 0;


	//Test HeroPurchase
	HeroPurchase* p;
	std::vector<HeroActor* >vecHero;
	std::vector<HeroActor* >vecHeroOnReady;
	std::vector<std::string> s;
	int num;

	//Test Equipment
	Equipment* e = nullptr;
	std::vector<Sprite*>vecEquipment;
	std::vector<std::string>vecEquipmentName;
	Vec2 touchedEquipmentPos;
	Sprite* touchedEquipment;
	std::string touchedEquipmentName;
	int chosedEquipmentNo = 0;
	bool isEquipmentTouched = false;
	int eqpnum = 0;

	////Test HeroSearchAI
	std::vector<Vec2> vece;
	std::vector<Vec2> vecm;
	std::vector<HeroActor*> testm;
	std::vector<HeroActor*> teste;
	std::vector<Vec2> posm;
	std::vector<Vec2> pose;
	int numMy = 0;
	int numAI = 0;
};
#endif

