#include "HeroPurchase.h"

HeroPurchase::HeroPurchase()
{
	onReadyNum = 0;
	b = false;
}
/*创建5个英雄*/
void HeroPurchase::drawHero()
{
	vecDrawHero.clear();
	vecHeroPrice.clear();
	srand((unsigned)(time(nullptr)));
	for (int i = 0; i < 5; i++)
	{
		int randHero = rand() % 5;
		vecDrawHero.push_back(heroName[randHero]);
		vecHeroPrice.push_back(heroPrice[randHero]);
	}
}
//放置五个英雄
void HeroPurchase::putHero()
{
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int n = 0;
	for (auto& i : vecDrawHero)
	{
		auto sprite = Sprite::create(i);
		sprite->setScale(HERO_SCALE_IN_PURCHASE);
		sprite->setPosition(visibleSize.width / putPos[n]+(n-2)*60, visibleSize.height / 2+98/2);
		n++;
		vecTemp.push_back(sprite);
		this->addChild(sprite);
	}
}
void HeroPurchase::putGold()
{
	int n = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto& i : vecHeroPrice)
	{
		auto gold = Sprite::create(GOLD);
		gold->setScale(GOLD_SCALE_IN_PURCHASE);//改金币图片大小
		gold->setPosition(visibleSize.width / putPos[n] + (n - 2) * 60-20, visibleSize.height / 2 - 98);
		vecGoldTemp.push_back(gold);
		this->addChild(gold);
		auto price = Label::createWithTTF(StringUtils::format("%d", vecHeroPrice[n]), "fonts/Marker Felt.ttf", 24);
		price->setPosition(visibleSize.width / putPos[n] + (n - 2) * 60-20+gold->getContentSize().width, visibleSize.height / 2 - 98);
		vecPriceTemp.push_back(price);
		this->addChild(price);
		n++;
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
	this->putGold();
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
		//auto& j = vecPriceTemp;
		if (i != nullptr)
		{
			auto heroLocation = i->getPosition();
			auto heroSize = i->getContentSize() * 0.3f;
			if (touchLocation.x > heroLocation.x - heroSize.width / 2 &&
				touchLocation.x < heroLocation.x + heroSize.width / 2 &&
				touchLocation.y > heroLocation.y - heroSize.height / 2 &&
				touchLocation.y < heroLocation.y + heroSize.height / 2)
			{
				int goldNow = Player::getInstance()->playerGold;
				int chessPrice = vecHeroPrice[n];
				if (Player::getInstance()->heroOnReadyNum < 8 && goldNow>0&& goldNow>= chessPrice)
				{
					//auto s = Sprite::create(vecDrawHero[n]);
					onReadyNum++;
					Player::getInstance()->playerGold -= vecHeroPrice[n];
					//tmp = Player::getInstance()->playerGold;
					vecOnReady.push_back(vecDrawHero[n]);
					Player::getInstance()->addHeroClick(vecDrawHero[n]);
					this->removeChild(i);
					this->removeChild(vecPriceTemp[n]);
					this->removeChild(vecGoldTemp[n]);
					//changed
					i = nullptr;
				}
			}
		}
		n++;
	}

	return true;
}

