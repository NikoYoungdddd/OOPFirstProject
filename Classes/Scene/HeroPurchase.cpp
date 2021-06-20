#include "HeroPurchase.h"

HeroPurchase::HeroPurchase()
{
	onReadyNum = 0;
	b = false;
}

void HeroPurchase::drawHero()
{
	vecDrawHero.clear();
	srand((unsigned)(time(nullptr)));
	for (int i = 0; i < 5; i++)
	{
		int randHero = rand() % 5;
		vecDrawHero.push_back(heroName[randHero]);
	}
}

void HeroPurchase::putHero()
{
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int n = 0;
	for (auto& i : vecDrawHero)
	{
		auto sprite = Sprite::create(i);
		sprite->setScale(HERO_SCALE_IN_PURCHASE);
		sprite->setPosition(winSize.width / putPos[n], winSize.height / 2);
		n++;
		vecTemp.push_back(sprite);
		this->addChild(sprite);
	}
}

bool HeroPurchase::init()
{
	if (!Node::init())
	{
		return true;
	}

	this->drawHero();
	this->putHero();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HeroPurchase::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

std::vector<std::string> HeroPurchase::getHero()
{
	return vecOnReady;
}

int HeroPurchase::getNum()
{
	return onReadyNum;
}
HeroPurchase* HeroPurchase::create()
{
	auto pRet = new HeroPurchase();
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

bool  HeroPurchase::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 touchLocation = touch->getLocation();
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int n = 0;
	for (auto& i : vecTemp)
	{
		if (i != nullptr)
		{
			auto heroLocation = i->getPosition();
			auto heroSize = i->getContentSize() * 0.3f;
			if (touchLocation.x > heroLocation.x - heroSize.width / 2 &&
				touchLocation.x < heroLocation.x + heroSize.width / 2 &&
				touchLocation.y > heroLocation.y - heroSize.height / 2 &&
				touchLocation.y < heroLocation.y + heroSize.height / 2)
			{
				//auto s = Sprite::create(vecDrawHero[n]);			
				unsigned int cost = 999;
				if (vecDrawHero[n] == "Tank.png")
					cost = 1;
				else if (vecDrawHero[n] == "Assasion.png")
					cost = 1;
				else if (vecDrawHero[n] == "ADC.png")
					cost = 2;
				else if (vecDrawHero[n] == "AP.png")
					cost = 2;
				else if (vecDrawHero[n] == "AOE.png")
					cost = 3;
				if (cost <= Player::getInstance()->playerGold)
				{
					onReadyNum++;
					Player::getInstance()->playerGold -= cost;
					vecOnReady.push_back(vecDrawHero[n]);
					Player::getInstance()->addHeroClick(vecDrawHero[n]);
					this->removeChild(i);
					i = nullptr;
				}
			}
		}
		n++;
	}

	return true;
}

