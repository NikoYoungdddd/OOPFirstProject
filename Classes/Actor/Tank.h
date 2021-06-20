#ifndef __HERO_TANK_H__
#define __HERO_TANK_H__

#include "HeroActor.h"

class Tank :public HeroActor
{
public:
	Tank();

	virtual void moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos);
	
	virtual void attack(const bool stay = false);
	
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false);

};
#endif

