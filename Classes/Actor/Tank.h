#ifndef __HERO_TANK_H__
#define __HERO_TANK_H__

#include "Actor/HeroActor.h"

class Tank :public HeroActor
{
public:
	Tank();

	virtual void attack(float f, const bool stay = false);
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false);
};
#endif

