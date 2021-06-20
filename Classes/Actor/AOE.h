#ifndef __HERO_AOE_H__
#define __HERO_AOE_H__

#include "Actor/HeroActor.h"


class AOE :public HeroActor
{
public:
	AOE();

	virtual void moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos);
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false);
	virtual void attack(const bool stay = false);
};
#endif



