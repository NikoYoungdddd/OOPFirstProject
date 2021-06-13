#include "HeroLayer.h"

#define TSET_PURCHASE 0
#define TEST_HERO_TOUCH 0
#define TEST_HERO_SEARCH_AI 1
#define TEST_PHYSICS 1
#define TEST_EQUIPMENT 0

HeroLayer::HeroLayer()
{
	num = 0;
	isHeroTouched = false;
	deltaX = 0;
	deltaY = 0;
	touchedHero = nullptr;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::pair<Vec2, bool> temp;
			temp.first = Vec2(BOARD_PIECE_SIZE * (i + 2.5f), BOARD_PIECE_SIZE * (j + 1.5f));
			temp.second = EMPTY;
			board[i][j] = temp;
		}
	}
}

void HeroLayer::testPush(const int n, const Vec2& pos, const int c)
{
	bool flag = true;
	int x = 0, y = 0;
	for (int i = 0; i < 8 && flag; i++)
	{
		for (int j = 0; j < 8 && flag; j++)
		{
			if (pos == board[i][j].first)
			{
				x = i;
				y = j;
				flag = false;
			}
		}
	}
	HeroActor* h = nullptr;
	if (n == 0)
	{
		h = new Tank();
	}
	else if (n == 1)
	{
		h = new ADC();
	}
	else if (n == 2)
	{
		h = new Assasion();
	}
	else if (n == 3)
	{
		h = new AOE();
	}
	else if (n == 4)
	{
		h = new AP();
	}
	h->autorelease();
	h->createHeroActor(c == 1);

	if (nullptr != h)
	{
		h->setHeroPos(pos);
		h->setBoardPos(x, y);
		if (c == 0)
		{
			numMy++;
			testm.push_back(h);
		}
		if (c == 1)
		{
			numAI++;
			teste.push_back(h);
			vece.push_back(pos);
		}
		this->addChild(h);
	}
}

void HeroLayer::removeFromPositonVec(const Vec2& pos, std::vector<Vec2>& posVec)
{
	for (auto iter = posVec.begin(); iter != posVec.end(); iter++)
	{
		if (*iter == pos)
		{
			posVec.erase(iter);
			break;
		}
	}
	return;
}

void HeroLayer::testCreate()
{
	srand(unsigned(time(nullptr)));
	for (int i = 0; i < 4; i++)
	{
		int mt = rand() % 5;
		int mx = rand() % 4;
		int my = rand() % 4 + 4;
		testPush(mt, board[mx][my].first, 0);
	}
	for (int i = 0; i < 4;)
	{
		int et = rand() % 5;
		int ex = rand() % 3 + 4;
		int ey = rand() % 4 + 2;
		if (!board[ex][ey].second)
		{
			i++;
			testPush(et, board[ex][ey].first, 1);
			board[ex][ey].second = OCCUPIED;
		}
		else
		{
			continue;
		}
	}
}

void HeroLayer::testPosAllocate(float dt)
{
	isUpdate = true;
	for (auto i : testm)
	{
		i->heroBuild();
		i->getEnemy(vece);
		i->searchEnemy(board);
		i->attack(0.2f);
	}
}

void HeroLayer::testEnemy(float dt)
{
	testPosAllocate(dt);
	isUpdate = true;
	for (auto v : testm)
	{
		vecm.push_back(v->getHeroStayPos());
	}

	for (auto v : teste)
	{
		vece.clear();
		v->heroBuild();
		int flag = 1;
		auto pos = v->getHeroPos();
		for (int i = 0; i < 8 && flag; i++)
		{
			for (int j = 0; j < 8 && flag; j++)
			{
				if (board[i][j].first == pos && board[i][j].second != LOCKED)
				{
					v->getEnemy(vecm);
					v->searchEnemy(board);
					v->attack(0.2f);
					flag = 0;
				}
				else if (board[i][j].first == pos)
				{
					v->getEnemy(vecm);
					v->searchEnemy(board, true);
					v->attack(0.2f, true);
					flag = 0;
				}
			}
		}
		auto pos2 = v->getHeroPos();
		vece.push_back(pos2);
	}
}

bool HeroLayer::init()
{
	if (!Layer::init())
	{
		return true;
	}

#if TEST_EQUIPMENT

	e = EquipmentLayer::create();
	this->addChild(e);

	h1 = new HeroAssasion();
	h1->createHeroActor("Assasion.png");
	h1->getEnemy(vec);
	h1->setHeroPos(Vec2(BOARD_PIECE_SIZE * 2.5f, BOARD_PIECE_SIZE * 7.5f));
	h1->autorelease();

	this->addChild(h1);
	vecHero.push_back(h1);

#endif

	//createPushActor("Tank.png", Vec2(BOARD_PIECE_SIZE * 2.5f, BOARD_PIECE_SIZE * 7.5f));

	//createPushActor("Assasion.png", Vec2(98 * 7.5f, 98 * 6.5f));

	//进一步 AI 功能的实现需要 暂停功能 和 倒计时->开始功能，暂时没法写
	//随机位置，随机英雄，仅测试
#if TEST_HERO_SEARCH_AI
	testCreate();

	//schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAllUser::tick1), 30.0f);
	//scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::testEnemy), 5.0f);
	//首先分配我方英雄位置
	//testPosAllocate();
	//然后敌方英雄判断是否被锁定，没有则移动
	testEnemy(0.2);

	
#endif

	//98 * 6.5f, 98 * 5.5f
	//98 * 7.5f, 98 * 6.5f
	//Vec2(98 * 2.5f, 98 * 7.5f)
	//Vec2(98 * 2.5f, 98 * 6.5f)
	//Vec2(98 * 2.5f, 98 * 5.5f)

	//配合购买层使用
#if TEST_HERO_TOUCH
	auto s1 = Sprite::create("star.png");
	auto s2 = Sprite::create("round.png");
	s1->setScale(0.3f);
	s1->setPosition(BOARD_PIECE_SIZE * 6.5f, BOARD_PIECE_SIZE * 5.5f);
	s2->setScale(0.3f);
	s2->setPosition(BOARD_PIECE_SIZE * 7.5f, BOARD_PIECE_SIZE * 6.5f);
	this->addChild(s1);
	this->addChild(s2);
	vec.push_back(s1->getPosition());
	vec.push_back(s2->getPosition());
#endif

	this->scheduleUpdate();

#if TSET_PURCHASE
	////购买英雄的层
	p = HeroPurchase::create();
	this->addChild(p);
#endif

	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = CC_CALLBACK_2(HeroLayer::onTouchBegan, this);
	//touchListener->onTouchMoved = CC_CALLBACK_2(HeroLayer::onTouchMoved, this);
	//touchListener->onTouchEnded = CC_CALLBACK_2(HeroLayer::onTouchEnded, this);
	//touchListener->onTouchCancelled = CC_CALLBACK_2(HeroLayer::onTouchCancelled, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


#if TEST_PHYSICS
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HeroLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
#endif

	return true;
}
HeroLayer* HeroLayer::create()
{
	HeroLayer* pRet = new HeroLayer();

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

void HeroLayer::createPushActor(const std::string& hero, const Vec2& putPos)
{
	HeroActor* h = nullptr;

	if (hero == "Tank.png")
	{
		h = new Tank();
	}
	else if (hero == "ADC.png")
	{
		h = new ADC();

	}
	else if (hero == "Assasion.png")
	{
		h = new Assasion();

	}
	else if (hero == "AOE.png")
	{
		h = new AOE();

	}
	else if (hero == "AP.png")
	{
		h = new AP();

	}
	else
		h = nullptr;

	if (nullptr != h)
	{
		h->autorelease();
		h->createHeroActor();
		h->setHeroPos(putPos);
		vecHeroOnReady.push_back(h);
		this->addChild(h);

	}
}

void HeroLayer::update(float ft)
{
#if TEST_HERO_SEARCH_AI
	if (isUpdate)
	{
		for (auto &i : testm)
		{
			if (nullptr != i)
			{			
				i->update();
				if (numMy && i->isAlive && !i->isTargetAlive)
				{
					i->isTargetAlive = true;
					i->getEnemy(vece);
					i->searchEnemy(board);
					i->attack(0.5f);
				}
			}
		}

		for (auto &i : teste)
		{
			if (nullptr != i)
			{				
				i->update();
				if (numAI && i->isAlive && !i->isTargetAlive)
				{
					i->isTargetAlive = true;
					i->getEnemy(vecm);
					i->searchEnemy(board);
					i->attack(0.5f);
				}
			}
		}

	}
#endif

#if TSET_PURCHASE
	s = p->getHero();
	if (!s.empty() && num != p->getNum())
	{
		std::string sname = *(s.end() - 1);
		num = p->getNum();
		createPushActor(sname, Vec2(98 * 1.5f, 98.f * ((8 - num) + 1.5f)));
	}
#endif

#if TEST_EQUIPMENT

	if (e != nullptr && e->isMoved)
	{
		std::string wn = e->getEquipment();
		Sprite* wp = Sprite::create(wn);
		wp->setScale(EQUIPMENT_SCALE);
		wp->setPosition(Vec2(98 * .5f, 98.f * ((8 - eqpnum) + 1.5f)));
		eqpnum++;
		this->addChild(wp);
		vecEquipment.push_back(wp);
		vecEquipmentName.push_back(wn);
		this->removeChild(e);
		e->isMoved = false;
		//e = nullptr;
	}

#endif



#if TEST_HERO_TOUCH

	if (isTest)
	{
		auto test = *(vecHero.end() - 1);
		test->getEnemy(vec);
		test->searchEnemy(board);
		test->attack(.2f);
		isTest = false;
	}
	if (!vecHero.empty())
	{
		for (auto i : vecHero)
		{
			i->update();
		}
	}

#endif
}

bool HeroLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 touchLocation = touch->getLocation();
	for (auto i : vecHeroOnReady)
	{
		chosedHeroNo = 0;
		if (nullptr != i)
		{
			auto heroLocation = i->getHeroPos();
			auto offset = touchLocation - heroLocation;
			auto hSize = i->getHeroSize() * HERO_SCALE;

			if (touchLocation.x > heroLocation.x - hSize.width / 2 &&
				touchLocation.x < heroLocation.x + hSize.width / 2 &&
				touchLocation.y > heroLocation.y - hSize.height / 2 &&
				touchLocation.y < heroLocation.y + hSize.height / 2)
			{
				isHeroTouched = true;
				deltaX = offset.x;
				deltaY = offset.y;
				touchedHeroPos = heroLocation;
				touchedHero = i;
				break;
			}
		}
		chosedHeroNo++;
	}

	if (!isHeroTouched)
	{
		chosedEquipmentNo = 0;
		for (auto i : vecEquipment)
		{
			if (nullptr != i)
			{
				auto equipmentLocation = i->getPosition();
				auto offset = touchLocation - equipmentLocation;
				auto eSize = i->getContentSize() * EQUIPMENT_SCALE;
				if (touchLocation.x > equipmentLocation.x - eSize.width / 2 &&
					touchLocation.x < equipmentLocation.x + eSize.width / 2 &&
					touchLocation.y > equipmentLocation.y - eSize.height / 2 &&
					touchLocation.y < equipmentLocation.y + eSize.height / 2)
				{
					isEquipmentTouched = true;
					deltaX = offset.x;
					deltaY = offset.y;
					touchedEquipmentPos = equipmentLocation;
					touchedEquipment = i;
					touchedEquipmentName = vecEquipmentName[chosedEquipmentNo];
					break;
				}
			}
			chosedEquipmentNo++;
		}
	}


	return true;
}
void HeroLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//for (auto &i : vecHeroOnReady)
	//{
	if (isHeroTouched /* && nullptr != i*/)
	{
		auto touchLocation = touch->getLocation();
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto hSize = touchedHero->getHeroSize() * HERO_SCALE;
		float x = touchLocation.x - deltaX;//記得減去偏移量
		float y = touchLocation.y - deltaY;

		if (x <= hSize.width / 2 + origin.x)//x到达屏幕左边界
			x = hSize.width / 2 + origin.x;
		else if (x >= visibleSize.width - hSize.width / 2)//x到达屏幕右边界
			x = visibleSize.width - hSize.width / 2;

		if (y <= hSize.height / 2 + origin.y)//y到达屏幕下边界
			y = hSize.height / 2 + origin.y;
		else if (y >= visibleSize.height - hSize.height / 2)//x到达屏幕上边界
			y = visibleSize.height - hSize.height / 2;

		//飞机跟随手指移动
		touchedHero->setHeroPos(Vec2(x, y));
	}

	//}

	if (isEquipmentTouched)
	{
		auto touchLocation = touch->getLocation();
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto eSize = touchedEquipment->getContentSize() * EQUIPMENT_SCALE;
		float x = touchLocation.x - deltaX;
		float y = touchLocation.y - deltaY;

		if (x <= eSize.width / 2 + origin.x)
			x = eSize.width / 2 + origin.x;
		else if (x >= visibleSize.width - eSize.width / 2)
			x = visibleSize.width - eSize.width / 2;
		if (y <= eSize.height / 2 + origin.y)
			y = eSize.height / 2 + origin.y;
		else if (y >= visibleSize.height - eSize.height / 2)
			y = visibleSize.height - eSize.height / 2;

		//飞机跟随手指移动
		touchedEquipment->setPosition(Vec2(x, y));
	}

	return;
}
void HeroLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (nullptr != touchedHero && isHeroTouched)
	{
		auto playerLocation = touchedHero->getHeroPos();
		bool isBack = true;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (playerLocation.x > (board[i][j].first.x - 49) && playerLocation.x < (board[i][j].first.x + 49) &&
					playerLocation.y >(board[i][j].first.y - 49) && playerLocation.y < (board[i][j].first.y + 49))
				{
					if (!board[i][j].second)
					{
						touchedHero->setHeroPos(board[i][j].first);
						vecHero.push_back(touchedHero);
						isBack = false;
						isTest = true;
						vecHeroOnReady.erase((vecHeroOnReady.begin() + chosedHeroNo));
						break;
					}
				}
			}
		}
		if (isBack)
			touchedHero->setHeroPos(touchedHeroPos);
	}

	if (nullptr != touchedEquipment && isEquipmentTouched)
	{
		auto equipmentLocation = touchedEquipment->getPosition();
		bool isBack = true;

		for (auto i : vecHero)
		{
			auto pos = i->getHeroPos();
			if (equipmentLocation.x > (pos.x - 49) && equipmentLocation.x < (pos.x + 49) &&
				equipmentLocation.y >(pos.y - 49) && equipmentLocation.y < (pos.y + 49))
			{
				touchedEquipment->setPosition(pos);
				isBack = false;
				std::string buffname = touchedEquipmentName;
				i->addBuff(buffname);
				break;
			}
		}

		if (isBack)
			touchedEquipment->setPosition(touchedEquipmentPos);
		else
		{
			vecEquipment.erase((vecEquipment.begin() + chosedEquipmentNo));
			vecEquipmentName.erase((vecEquipmentName.begin() + chosedEquipmentNo));
			this->removeChild(touchedEquipment);
		}
	}

	isHeroTouched = false;
	isEquipmentTouched = false;
}
void HeroLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_even)
{
	isHeroTouched = false;
	isEquipmentTouched = false;
}

bool HeroLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		int tagA = nodeA->getTag();
		int tagB = nodeB->getTag();
		if (tagA == TAG_AISIDE && tagB == TAG_MY_BULLET)
		{
			auto tempActor = dynamic_cast<HeroActor*>(nodeA->getParent());
			auto tempBullet = dynamic_cast<HeroBullet*>(nodeB->getParent());
			tempActor->getDamaged(tempBullet->getBulletDamage());

			if (!tempActor->isAlive)
			{
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				tempActor->selfDied();
				attackActor->enemyDied();
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second = EMPTY;
				auto pos = tempActor->getHeroPos();
				this->removeFromPositonVec(pos,vece);
				numAI--;
			}
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (tagB == TAG_AISIDE && tagA == TAG_MY_BULLET)
		{
			auto tempActor = dynamic_cast<HeroActor*>(nodeB->getParent());
			auto tempBullet = dynamic_cast<HeroBullet*>(nodeA->getParent());
			tempActor->getDamaged(tempBullet->getBulletDamage());

			if (!tempActor->isAlive)
			{
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				tempActor->selfDied();
				attackActor->enemyDied();
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second = EMPTY;
				auto pos = tempActor->getHeroPos();
				this->removeFromPositonVec(pos, vece);
				numAI--;
			}
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (tagA == TAG_MYSIDE && tagB == TAG_AI_BULLET)
		{
			auto tempActor = dynamic_cast<HeroActor*>(nodeA->getParent());
			auto tempBullet = dynamic_cast<HeroBullet*>(nodeB->getParent());
			tempActor->getDamaged(tempBullet->getBulletDamage());

			if (!tempActor->isAlive)
			{
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				tempActor->selfDied();
				attackActor->enemyDied();
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second = EMPTY;
				auto pos = tempActor->getHeroPos();
				this->removeFromPositonVec(pos, vecm);
				numMy--;
			}
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (tagB == TAG_MYSIDE && tagA == TAG_AI_BULLET)
		{
			auto tempActor = dynamic_cast<HeroActor*>(nodeB->getParent());
			auto tempBullet = dynamic_cast<HeroBullet*>(nodeA->getParent());
			tempActor->getDamaged(tempBullet->getBulletDamage());

			if (!tempActor->isAlive)
			{
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				tempActor->selfDied();				
				attackActor->enemyDied();
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second = EMPTY;
				auto pos = tempActor->getHeroPos();
				this->removeFromPositonVec(pos, vecm);
				numMy--;
			}
			nodeA->removeFromParentAndCleanup(true);
		}
	}
	return true;
}
