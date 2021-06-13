#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "Const/Const.h"

class Equipment : public Node
{
public:
	Equipment();
	~Equipment();
	virtual bool init();
	static Equipment* create();

	std::string getEquipment()const;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	bool isMoved = false;
private:

	Sprite* equipment = nullptr;
	bool alreadyCreateEquipment = false;
	std::string equipmentName;
};
#endif