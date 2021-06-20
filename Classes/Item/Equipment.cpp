#include "Equipment.h"

Equipment::Equipment(const Vec2& pos)
{
	alreadyCreateEquipment = false;
	
	srand((unsigned)(time(nullptr)));
	if (alreadyCreateEquipment == false)
	{
		srand((unsigned)(time(nullptr)));
		int randName = rand() % 4;
		equipment = Sprite::create(weaponName[randName]);
		equipmentName = weaponName[randName];
		equipment->setScale(EQUIPMENT_SCALE);
		equipment->setPosition(pos);
		alreadyCreateEquipment = true;
		this->addChild(equipment);
	}
}

Equipment::~Equipment()
{

}


bool Equipment::init()
{
	if (!Node::init())
	{
		return true;
	}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Equipment::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}


bool Equipment::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 touchLocation = touch->getLocation();

	if (equipment != nullptr)
	{
		auto equipmentPosition = equipment->getPosition();
		auto equipmentSize = equipment->getContentSize() * EQUIPMENT_SCALE;
		if (touchLocation.x > equipmentPosition.x - equipmentSize.width / 2 &&
			touchLocation.x <equipmentPosition.x + equipmentSize.width / 2 &&
			touchLocation.y > equipmentPosition.y - equipmentSize.height / 2 &&
			touchLocation.y < equipmentPosition.y + equipmentSize.height / 2)
		{
			this->removeChild(equipment);
			equipment = nullptr;
			isMoved = true;
		}
	}
	return true;
}


Equipment* Equipment::create(const Vec2& pos)
{
	auto pRet = new Equipment(pos);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		if (pRet != nullptr)
		{
			delete pRet;
			pRet = nullptr;
		}
		return nullptr;
	}

}


std::string Equipment::getEquipment()const
{
	return equipmentName;
}

