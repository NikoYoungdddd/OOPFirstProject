#ifndef __HERO_PURCHASE_H__
#define __HERO_PURCHASE_H__

#include"Const/Const.h"
#include"Player.h"
class HeroPurchase :public Node
{
public:

	HeroPurchase();

	virtual bool init();

	static HeroPurchase* create();

	void drawHero();

	void putHero();
	void putGold();
	std::vector<std::string> getHero();

	int getNum();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

private:

	std::vector<std::string> vecDrawHero;
	std::vector<std::string> vecOnReady;
	std::vector<int> vecHeroPrice;
	std::vector<Label*> vecPriceTemp;
	std::vector<Sprite*> vecGoldTemp;
	std::vector<Sprite*> vecTemp;
	int onReadyNum;
	bool b;
};
#endif


