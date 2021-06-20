#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "Const/Const.h"

class Equipment : public Node
{
public:
	Equipment(const Vec2& pos);
	~Equipment();
	virtual bool init();
	static Equipment* create(const Vec2& pos);

	std::string getEquipment()const;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	bool isMoved = false;
private:

	Sprite* equipment = nullptr;
	bool alreadyCreateEquipment = false;
	std::string equipmentName;
	
};
#endif