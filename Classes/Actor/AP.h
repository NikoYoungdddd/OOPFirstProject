#ifndef __HERO_AP_H__
#define __HERO_AP_H__


#include "HeroActor.h"


class AP :public HeroActor
{
public:
	AP();

	virtual void moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos);
	
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false);
	
	virtual void attack(const bool stay = false);

};
#endif





