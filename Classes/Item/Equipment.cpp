#include "Equipment.h"

Equipment::Equipment()
{
	alreadyCreateEquipment = false;
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
	srand((unsigned)(time(nullptr)));
	if (alreadyCreateEquipment == false)
	{
		srand((unsigned)(time(nullptr)));
		int randName = rand() % 4;
		equipment = Sprite::create(weaponName[randName]);
		equipmentName = weaponName[randName];
		equipment->setScale(EQUIPMENT_SCALE);
		equipment->setPosition(Vec2(BOARD_PIECE_SIZE * (5 + 2.5f), BOARD_PIECE_SIZE * (5 + 1.5f)));
		alreadyCreateEquipment = true;
		this->addChild(equipment);
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
			removeChild(equipment);
			equipment = nullptr;
			isMoved = true;
		}
	}
	return true;
}

Equipment* Equipment::create()
{
	auto pRet = new Equipment();
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

