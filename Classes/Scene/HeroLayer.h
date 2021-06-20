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

	//´ÓÈİÆ÷ÖĞÉ¾³ıÔªËØ
	template<class T>
	void removeFromVec(const T& pos, std::vector<T>& posVec);

	//´´½¨Ó¢ĞÛ£¬²ÎÊı £ºÖÖÀà  ¡¢ÆåÅÌx  ¡¢ÆåÅÌy   ¡¢ÊÇ·ñÎªÎÒ·½´´½¨ falseÊÇÊÇÎÒ·½´´½¨
	void createHero(const int type, const int x, const int y, bool isAI);

	void createHeroOnReady(const int type);
	void createHeroOnBoard(HeroActor* hero, const int x, const int y);

	//½ö²âÊÔÓÃ
	void testCreate(float dt);
	//²úÉúÓëÎÒ·½ÏàÍ¬¸öÊıµÄÓ¢ĞÛ
	void testAI(float dt);
	//¿ÉÒ»Ö±ÓÃ
	void allocateMyHero();  //ÎÒ·½ÏÈÊÖ
	void allocateAIHero();  //Î´±»ÎÒ·½Ëø¶¨µÄÆå×Ó¿ÉÒÔÒÆ¶¯
	//¸üĞÂÎ»ÖÃÈİÆ÷
	void updateHeroPos(bool isAI);

	//¿ªÊ¼ĞÂµÄ»ØºÏ
	void startRound(float dt);

	//ÔİÊ±ÎŞÓÃ
	void searchAgain(std::vector<HeroActor*>&vecHero,const std::vector<Vec2>& vecPos,const int side);
<<<<<<< HEAD

	//»Øµ½Ã¿¾Ö¿ªÊ¼µÄÎ»ÖÃ
	void boardReset(float dt);
	//¿ÕÊµÏÖ£¬ÅäºÏµ÷¶ÈÆ÷²úÉúÑÓÊ±×÷ÓÃ
	void timeCountDown(float dt);


	void updateEquipment();

	void updateHeros();

=======

	//å›åˆ°æ¯å±€å¼€å§‹çš„ä½ç½®
	void boardReset(float dt);
	//ç©ºå®ç°ï¼Œé…åˆè°ƒåº¦å™¨äº§ç”Ÿå»¶æ—¶ä½œç”¨
	void timeCountDown(float dt);


	void updateEquipment();

	void updateHeros();

>>>>>>> main
	void createEquipment(const Vec2& pos);


	//Ä¿Ç°Ö§³Ö
	//3-4¸öÔÚ×¼±¸Î»ÖÃ
	//1¸öÔÚÆåÅÌ£¬2¸ö×¼±¸
	//2¸öÔÚÆåÅÌ£¬1¸öÔÚ×¼±¸
	void heroStarsUP();
	
public:
	std::pair<Vec2, int> board[8][8];
	std::pair<Vec2, int> readyPos[8];
	std::pair<Vec2, int> equipmentPos[8];
	bool isUpdate = false;  //¸üĞÂÑªÌõ
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
	std::vector<Vec2> vecAIHeroPos;  //µĞ·½Î»ÖÃ
	std::vector<Vec2> vecMyHeroPos;  //ÎÒ·½Î»ÖÃ
	std::vector<HeroActor*> vecMyHeros;  //ÎÒ·½
	std::vector<HeroActor*> vecAIHeros;  //µĞ·½	
	int numMyHeros = 0;
	int numAIHeros = 0;

	//½öÔÚresetÓÃ
	std::vector<Vec2>vecMyHeroReset;  //±£´æÃ¿¾Ö¿ªÊ¼Ç°µÄÎ»ÖÃ
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

