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

	//随机获取五个
	void drawHero();

	//放置五个英雄
	void putHero();

	//放置每个人的金币
	void putGold();

	//获取全部购买的英雄
	std::vector<std::string> getHero();

	//获取总的人数
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



