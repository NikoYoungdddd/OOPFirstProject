
#include "HeroLayer.h"

HeroLayer::HeroLayer()
{
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

	for (int i = 0; i < 8; i++)
	{
		readyPos[i].first = Vec2(98 * 1.5f, 98.f * ((7 - i) + 1.5f));
		readyPos[i].second = EMPTY;
	}
	for (int i = 0; i < 8; i++)
	{
		equipmentPos[i].first = Vec2(98 * .5f, 98.f * ((7 - i) + 1.5f));
		equipmentPos[i].second = EMPTY;
	}
}

template<class T>
void HeroLayer::removeFromVec(const T& elem, std::vector<T>& elemVec)
{
	for (auto iter = elemVec.begin(); iter != elemVec.end(); iter++)
	{
		if (*iter == elem)
		{
			elemVec.erase(iter);
			break;
		}
	}
	return;
}

void HeroLayer::testCreate(float dt)
{
	srand(unsigned(time(nullptr)));
	for (int i = 0; i < 4;)
	{
		int mytype = rand() % 5;
		int myx = rand() % 4;
		int myy = rand() % 4 + 4;
		if (!board[myx][myy].second)
		{
			i++;
			createHero(mytype, myx, myy, false);
			board[myx][myy].second = OCCUPIED;
		}
	}
	for (int i = 0; i < 4;)
	{
		int aitype = rand() % 5;
		int aix = rand() % 3 + 4;
		int aiy = rand() % 4 + 2;
		if (!board[aix][aiy].second)
		{
			i++;
			createHero(aitype, aix, aiy, true);
			board[aix][aiy].second = OCCUPIED;
		}
	}
}

void HeroLayer::testAI(float dt)
{
	if (numMyHeros != numAIHeros)
		for (int i = 0; i <= numMyHeros - numAIHeros;)
		{

			int aitype = rand() % 5;
			int aix = rand() % 3 + 4;
			int aiy = rand() % 4 + 2;
			if (!board[aix][aiy].second)
			{
				i++;
				createHero(aitype, aix, aiy, true);
				board[aix][aiy].second = OCCUPIED;
			}
		}
}
void  HeroLayer::createHeroOnReady(const int type)
{
	HeroActor* hero = nullptr;
	if (type == Type_Tank)
		hero = new Tank();
	else if (type == Type_Assasion)
		hero = new Assasion();
	else if (type == Type_ADC)
		hero = new ADC();
	else if (type == Type_AP)
		hero = new AP();
	else if (type == Type_AOE)
		hero = new AOE();
	if (nullptr != hero)
	{
		hero->autorelease();
		hero->createHeroActor();
		Vec2 pos;
		for (int i = 0; i < 8; i++)
		{
			if (!readyPos[i].second)
			{
				pos = readyPos[i].first;
				readyPos[i].second = OCCUPIED;
				hero->setBoardPos(-1, i);
				break;
			}
		}
		arrayHeroNum[type]++;
		hero->setHeroPos(pos);
		this->addChild(hero);
		vecHeroOnReady.push_back(hero);
	}
}

void HeroLayer::createHeroOnBoard(HeroActor* hero, const int x, const int y)
{
	hero->setHeroPos(board[x][y].first);
	hero->setBoardPos(x,y);
	vecMyHeroReset.push_back(board[x][y].first);
	vecMyHeroBoardPos.push_back(std::make_pair(x, y));
	board[x][y].second = OCCUPIED;
	hero->heroBuild();
	numMyHeros++;
	vecMyHeros.push_back(hero);
}
void HeroLayer::createHero(const int type, const int x, const int y, bool isAI)
{
	HeroActor* hero = nullptr;
	if (type == Type_Tank)
		hero = new Tank();
	else if (type == Type_Assasion)
		hero = new Assasion();
	else if (type == Type_ADC)
		hero = new ADC();
	else if (type == Type_AP)
		hero = new AP();
	else if (type == Type_AOE)
		hero = new AOE();
	if (nullptr != hero)
	{
		hero->autorelease();
		hero->createHeroActor(isAI);
		hero->setHeroPos(board[x][y].first);
		hero->setBoardPos(x, y);
		hero->heroBuild();
		if (!isAI)
		{
			numMyHeros++;
			vecMyHeros.push_back(hero);
			vecMyHeroReset.push_back(board[x][y].first);
			vecMyHeroBoardPos.push_back(std::make_pair(x, y));
		}
		if (isAI)
		{
			numAIHeros++;
			vecAIHeros.push_back(hero);
			vecAIHeroPos.push_back(board[x][y].first);
			vecAIHeroReset.push_back(board[x][y].first);
			vecAIHeroBoardPos.push_back(std::make_pair(x, y));
		}
		this->addChild(hero);
	}
}

void HeroLayer::heroStarsUP()
{
	int numOnBoard = 0, numOnReady = 0;
	int herotype = 6;
	for (int type = 0; type < 5; type++)
	{
		if (arrayHeroNum[type] >= 3)
		{
			herotype = type;
			for (auto hero : vecMyHeros)
			{
				if (hero->m_Type == type && hero->m_Star == 1)
				{
					numOnBoard++;
				}
			}
			for (auto hero : vecHeroOnReady)
			{
				if (hero->m_Type == type && hero->m_Star == 1)
				{
					numOnReady++;
				}
			}
			if (numOnBoard + numOnReady >= 3)
				arrayHeroNum[herotype] -= 2;
			break;
		}
	}
	if (numOnBoard + numOnReady >= 3)
	{
		if (numOnBoard != 0)
		{
			if (numOnBoard == 1)
			{
				for (auto &hero : vecMyHeros)
				{
					if (hero->m_Type == herotype && hero->m_Star == 1)
					{
						hero->starsUP();
						break;
					}
				}
				int n = 0, i = 0;
				int arr[5]{};
				for (auto hero : vecHeroOnReady)
				{					
					if (hero->m_Type == herotype && hero->m_Star == 1)
					{
						arr[n++] = i;
						if (n <= 2)
						{
							auto pos = hero->getBoardPos();
							readyPos[pos.second].second = EMPTY;
							this->removeChild(hero);
						}
					}
					i++;
				}
				vecHeroOnReady.erase(vecHeroOnReady.begin() + arr[1]);
				vecHeroOnReady.erase(vecHeroOnReady.begin() + arr[0]);
			}
			else if (numOnBoard == 2)
			{
				int n = 0, i = 0;
				int arr[5]{};
				bool isFind = false;
				for (auto& hero : vecMyHeros)
				{
					if (!isFind)
					{
						if (hero->m_Type == herotype && hero->m_Star == 1)
						{
							isFind = true;
							arr[n++] = i;
						}
					}
					else
					{
						if (hero->m_Type == herotype && hero->m_Star == 1)
						{
							arr[n++] = i;
							if (n <= 2)
							{
								auto pos = hero->getBoardPos();
								board[pos.first][pos.second].second = EMPTY;
								this->removeChild(hero);
							}
						}
					}
					i++;
				}
				vecMyHeros.erase(vecMyHeros.begin() + arr[1]);

				int m = 0;
				for (auto &hero : vecHeroOnReady)
				{
					if (hero->m_Type == herotype && hero->m_Star == 1)
					{
						this->removeChild(hero);
						break;
					}
					m++;
				}
				vecHeroOnReady.erase(vecHeroOnReady.begin() + m);
			}
		}
		else
		{
			bool isFind = false;
			int arr[8]{};
			int n = 0, i = 0;
			for (auto& hero : vecHeroOnReady)
			{			
				if (!isFind)
				{
					if (hero->m_Type == herotype && hero->m_Star == 1)
					{
						isFind = true;
						arr[n++] = i;
					}
				}
				else
				{
					if (hero->m_Type == herotype && hero->m_Star == 1)
					{
						arr[n++] = i;
						if (n <= 3)
						{
							auto pos = hero->getBoardPos();
							readyPos[pos.second].second = EMPTY;
							this->removeChild(hero);
						}
					}
				}
				i++;
			}
			vecHeroOnReady.erase(vecHeroOnReady.begin() + arr[2]);
			vecHeroOnReady.erase(vecHeroOnReady.begin() + arr[1]);
			vecHeroOnReady[arr[0]]->starsUP();
		}
	}
}

void  HeroLayer::updateHeroPos(bool isAI)
{
	if (!isAI)
	{
		vecMyHeroPos.clear();
		for (auto hero : vecMyHeros)
			if (hero->isAlive)
				vecMyHeroPos.push_back(hero->getHeroStayPos());
	}
	else
	{
		vecAIHeroPos.clear();
		for (auto hero : vecAIHeros)
			if (hero->isAlive)
				vecAIHeroPos.push_back(hero->getHeroStayPos());
	}
}

void HeroLayer::searchAgain(std::vector<HeroActor*>& vecHero, const std::vector<Vec2>& vecPos, const int side)
{
	
}

void HeroLayer::allocateMyHero()
{
	isUpdate = true;
	for (auto hero : vecMyHeros)
	{
		hero->getEnemy(vecAIHeroPos);
		hero->searchEnemy(board);
		hero->attack();
	}
}

void HeroLayer::allocateAIHero()
{
	isUpdate = true;
	vecMyHeroPos.clear();
	for (auto hero : vecMyHeros)
	{
		if (hero->isAlive)
			vecMyHeroPos.push_back(hero->getHeroStayPos());
	}
	vecAIHeroPos.clear();
	for (auto hero : vecAIHeros)
	{
		auto boardPos = hero->getBoardPos();
		int boardStatus = board[boardPos.first][boardPos.second].second;
		bool isLocked = ((boardStatus >= LOCKED) && (boardStatus != OCCUPIED));
		hero->getEnemy(vecMyHeroPos);
		hero->searchEnemy(board, isLocked);
		hero->attack(isLocked);
		vecAIHeroPos.push_back(hero->getHeroPos());		
	}
}

void HeroLayer::startRound(float dt)
{
	allocateMyHero();
	allocateAIHero();
}

void HeroLayer::boardReset(float dt)
{
	int n = 0, m = 0;
	for (auto& hero : vecMyHeros)
	{
		hero->resetHero();
		hero->setHeroPos(vecMyHeroReset[n]);
		hero->setBoardPos(vecMyHeroBoardPos[n].first, vecMyHeroBoardPos[n].second);
		n++;
	}
	vecMyHeroPos.clear();
	vecMyHeroPos = vecMyHeroReset;
	numMyHeros = vecMyHeros.size();

	for (auto& hero : vecAIHeros)
	{
		hero->resetHero();
		hero->setHeroPos(vecAIHeroReset[m]);
		hero->setBoardPos(vecAIHeroBoardPos[m].first, vecAIHeroBoardPos[m].second);
		m++;
	}
	vecAIHeroPos.clear();
	vecAIHeroPos = vecAIHeroReset;
	numAIHeros = vecAIHeros.size();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j].second = EMPTY;
			for (auto pos : vecAIHeroReset)
				if (pos == board[i][j].first)
					board[i][j].second = OCCUPIED;

			for (auto pos : vecMyHeroReset)
				if (pos == board[i][j].first)
					board[i][j].second = OCCUPIED;
		}
	}
	
	isStartNewRound = true;
}

void HeroLayer::timeCountDown(float dt)
{
//	isGameStart = true;
}

void HeroLayer::updateHeros()
{
	if (isUpdate)
	{
		for (auto& hero : vecMyHeros)
		{
			if (nullptr != hero)
			{
				hero->update();
				auto tlct = hero->getTargetBoardPos();
				int isTargetEmpty = board[tlct.first][tlct.second].second;
				if (numMyHeros && hero->isAlive && (!hero->isTargetAlive || (isTargetEmpty == EMPTY))
					&& !vecAIHeroPos.empty())
				{
					updateHeroPos(true);
					auto boardPos = hero->getBoardPos();
					int boardStatus = board[boardPos.first][boardPos.second].second;
					bool isLocked = ((boardStatus >= LOCKED) && boardStatus != OCCUPIED);
					hero->isTargetAlive = true;
					hero->getEnemy(vecAIHeroPos);
					hero->searchEnemy(board, isLocked);
					hero->attack(isLocked);
				}
			}
		}

		for (auto& hero : vecAIHeros)
		{

			if (nullptr != hero)
			{
				hero->update();
				auto tlct = hero->getTargetBoardPos();
				int isTargetEmpty = board[tlct.first][tlct.second].second;
				if (numAIHeros && hero->isAlive && (!hero->isTargetAlive || (isTargetEmpty == EMPTY))
					&& !vecMyHeroPos.empty())
				{
					updateHeroPos(false);
					auto boardPos = hero->getBoardPos();
					int boardStatus = board[boardPos.first][boardPos.second].second;
					bool isLocked = ((boardStatus >= LOCKED) && boardStatus != OCCUPIED);
					hero->isTargetAlive = true;
					hero->getEnemy(vecMyHeroPos);
					hero->searchEnemy(board, isLocked);
					hero->attack(isLocked);
				}
			}
		}
		if (numAIHeros == 0 || numMyHeros == 0)
		{
			if (numAIHeros == 0)
			{
				Player::getInstance()->playerGold += 5;
				Player::getInstance()->enemyHP -= 5;
				AIGold += 2;
			}
			else
			{
				Player::getInstance()->playerGold += 2;
				Player::getInstance()->playerHP -= 5;
				AIGold += 5;
			}
			

			isUpdate = false;
			createEquipment(board[5][5].first);
			//定时器是同时开始的
			scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::boardReset), ROUND_END_TIME);
			scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::testAI), 5.0f);
			scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::startRound), ROUND_END_TIME + PREPARE_TIME);
		}
	}
	if (!isGameStart)
	{
		isGameStart = true;
		scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::timeCountDown), ROUND_END_TIME*2);
		scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::testAI), ROUND_END_TIME * 3);
		scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::startRound), ROUND_END_TIME * 4);
	}
}

void  HeroLayer::createEquipment(const Vec2& pos)
{
	auto equip = Equipment::create(pos);
	this->addChild(equip);
	vecEquipmentUncollected.push_back(equip);
}

void HeroLayer::updateEquipment()
{
	for (auto& equip : vecEquipmentUncollected)
	{
		if (equip != nullptr && equip->isMoved)
		{
			std::string eName = equip->getEquipment();
			Sprite* equipSprite = Sprite::create(eName);
			equipSprite->setScale(EQUIPMENT_SCALE);
			equipSprite->setPosition(Vec2(98 * 2.5f + eqpnum * 25 + 25 / 2, 98 * 10 - 25 / 2)); eqpnum++;
			this->addChild(equipSprite);
			vecEquipment.push_back(equipSprite);
			vecEquipmentName.push_back(eName);
			equip->isMoved = false;
			this->removeFromVec(equip, vecEquipmentUncollected);
			this->removeChild(equip);			
		}
	}
}
bool HeroLayer::init()
{
	if (!Layer::init())
	{
		return true;
	}
	
	
	createEquipment(board[5][5].first);
	//scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::testCreate), 5.0f);
	//scheduleOnce(CC_SCHEDULE_SELECTOR(HeroLayer::startRound), 10.0f);
	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HeroLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HeroLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HeroLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HeroLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HeroLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

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

void HeroLayer::update(float ft)
{
	heroStarsUP();
	updateEquipment();
	updateHeros();
}

bool HeroLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Vec2 touchLocation = touch->getLocation();
	chosedHeroNo = 999;
	int n = 0;
	for (auto i : vecHeroOnReady)
	{
		n++;
		if (nullptr != i)
		{
			auto heroLocation = i->getHeroPos();
			auto offset = touchLocation - heroLocation;
			auto hSize = i->getHeroSize() * HERO_SCALE * HERO_TOUCH_SIZE;

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
				chosedHeroNo=n;
				break;
			}
		}
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
	
	if (isHeroTouched)
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
						auto pos =touchedHero->getBoardPos();
						if (pos.first == -1)
							readyPos[pos.second].second = EMPTY;
						if (board[i][j].second == EMPTY)
						{
							createHeroOnBoard(touchedHero,i,j);
							//touchedHero->setHeroPos(board[i][j].first);
							//board[i][j].second = OCCUPIED;
							//touchedHero->setBoardPos(i, j);
							//vecMyHeros.push_back(touchedHero);
							isBack = false;
							if (chosedHeroNo == 0)
								vecHeroOnReady.erase((vecHeroOnReady.begin()));
							else if (chosedHeroNo <= vecHeroOnReady.size())
								vecHeroOnReady.erase((vecHeroOnReady.begin() + chosedHeroNo - 1));
							chosedHeroNo = 999;
							break;
						}
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

		for (auto i : vecMyHeros)
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
				if (!tempActor->dieOnce)
				{
					tempActor->selfDied();				
					auto pos = tempActor->getHeroPos();
					this->removeFromVec(pos, vecAIHeroPos);
					numAIHeros--;
					auto tlct = tempActor->getTargetBoardPos();
					if (board[tlct.first][tlct.second].second != EMPTY)
						board[tlct.first][tlct.second].second--;
					tempActor->dieOnce = true;
				}
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second--;
				if (board[lct.first][lct.second].second == EMPTY)
				{
					tempActor->changeHeroTag(TAG_UNATTACKED);
				}
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				attackActor->enemyDied();
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
				if (!tempActor->dieOnce)
				{
					tempActor->selfDied();				
					auto pos = tempActor->getHeroPos();
					this->removeFromVec(pos, vecAIHeroPos);
					numAIHeros--;	
					auto tlct = tempActor->getTargetBoardPos();
					if (board[tlct.first][tlct.second].second != EMPTY)
						board[tlct.first][tlct.second].second--;
					tempActor->dieOnce = true;
				}
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second--;
				if (board[lct.first][lct.second].second == EMPTY)
				{
					tempActor->changeHeroTag(TAG_UNATTACKED);
				}
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				attackActor->enemyDied();
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
				if (!tempActor->dieOnce)
				{
					tempActor->selfDied();					
					auto pos = tempActor->getHeroPos();
					this->removeFromVec(pos, vecMyHeroPos);
					numMyHeros--;
					auto tlct = tempActor->getTargetBoardPos();
					if (board[tlct.first][tlct.second].second != EMPTY)
						board[tlct.first][tlct.second].second--;
					tempActor->dieOnce = true;
				}
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second--;
				if (board[lct.first][lct.second].second == EMPTY)
				{
					tempActor->changeHeroTag(TAG_UNATTACKED);
				}
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				attackActor->enemyDied();
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
				if (!tempActor->dieOnce)
				{
					tempActor->selfDied();
					auto pos = tempActor->getHeroPos();
					this->removeFromVec(pos, vecMyHeroPos);
					numMyHeros--;
					auto tlct = tempActor->getTargetBoardPos();
					if (board[tlct.first][tlct.second].second != EMPTY)
						board[tlct.first][tlct.second].second--;
					tempActor->dieOnce = true;
				}
				std::pair<int, int> lct = tempActor->getBoardPos();
				board[lct.first][lct.second].second--;
				if (board[lct.first][lct.second].second == EMPTY)
				{
					tempActor->changeHeroTag(TAG_UNATTACKED);
				}
				auto attackActor = dynamic_cast<HeroActor*>(tempBullet->getParent());
				attackActor->enemyDied();				
				
			}
			nodeA->removeFromParentAndCleanup(true);
		}
	}
	return true;
}
