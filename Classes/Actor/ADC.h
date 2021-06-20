#ifndef __HERO_ADC_H__
#define __HERO_ADC_H__

#include "HeroActor.h"

class ADC :public HeroActor
{

public:
	ADC();

	virtual void moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos);
	
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false);
	
	virtual void attack(const bool stay = false);

};
#endif



