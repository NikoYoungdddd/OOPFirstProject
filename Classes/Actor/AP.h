#ifndef __HERO_AP_H__
#define __HERO_AP_H__


#include "Actor/HeroActor.h"


class AP :public HeroActor
{
public:
	AP();


	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false);
	virtual void attack(float f, const bool stay = false);
};
#endif




