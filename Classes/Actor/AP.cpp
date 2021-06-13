#include"AP.h"

AP::AP()
{
	this->m_HP = 2400;
	this->m_Status.m_Damage.m_PhysicalDamage = 0;
	this->m_Status.m_Damage.m_PowerDamage = 300;
	this->m_Status.m_Defense.m_PhysicalDefense = 50;
	this->m_Status.m_Defense.m_PowerDefense = 200;
	this->m_Status.m_AttackFrequency = 2;
	this->m_Type = Type_AP;
	this->m_Cost = 2;
	boardX = -1;
	boardY = -1;
}


void AP::searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay)
{
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//myHero->setPosition(this->getPosition());

	Vec2 startDest = myHero->getPosition();
	Vec2 endDest = *(vecPos.begin());
	Vec2 stayPos = startDest;
	float shortestLen = sqrt((startDest.x - endDest.x) * (startDest.x - endDest.x) +
		(startDest.y - endDest.y) * (startDest.y - endDest.y));

	int randS = vecPos.size();
	srand((unsigned)(time(nullptr)));
	int randM = rand() % randS;

	endDest = vecPos[randM];
	float len = sqrt((startDest.x - endDest.x) * (startDest.x - endDest.x) +
		(startDest.y - endDest.y) * (startDest.y - endDest.y));

	/*for (auto i : vecPos)
	{
		auto tempDest = i;
		float len = sqrt((startDest.x - tempDest.x) * (startDest.x - tempDest.x) +
			(startDest.y - tempDest.y) * (startDest.y - tempDest.y));
		if (len < shortestLen)
		{
			shortestLen = len;
			endDest = tempDest;
		}
	}*/

	int flag = 1;
	if (!stay)
		for (int i = 0; i < 8 && flag; i++)
		{
			for (int j = 0; j < 8 && flag; j++)
			{
				if (board[i][j].first == endDest)
				{
					board[i][j].second = LOCKED;
					//for (int k = 0; k < 5; k++)
					while (1)
					{
						int randP = rand() % 10;
						int x = ADCSearch[randP][0], y = ADCSearch[randP][1];
						if (i + x < 0 || i + x >= 8 || i + y < 0 || i + y >= 8)
							continue;
						if (!board[i + x][j + y].second)
						{
							//数组可能会越界
							stayPos = board[i + x][j + y].first;
							board[i + x][j + y].second = OCCUPIED;
							boardX = i + x;
							boardY = j + y;
							flag = 0;
							break;
						}
					}
				}
			}
		}

	targetPos = endDest;
	attackPos = stayPos;
	moveDuration = shortestLen / SPEED;
}

void AP::attack(float ft, const bool stay)
{
	float ff = ATTACK_DURATION_MARK / m_Status.m_AttackFrequency;

	auto shoot = CallFunc::create([=]() {
		auto attackBullet = HeroBullet::create(heroBulletName[m_Type], this->m_Status.m_Damage);
		attackBullet->setBulletPos(myHero->getPosition());
		attackBullet->setBulletScale(heroBulletScale[m_Type]);
		attackBullet->bulletBuild(isEnemy);
		attackBullet->setBulletRotation(targetPos);
		this->addChild(attackBullet);

		
		auto pointMove = MoveTo::create(ff, targetPos);
		auto pointMoveDone = RemoveSelf::create();
		attackBullet->shootBullet(Sequence::create(pointMove, pointMoveDone, nullptr));
		});

	auto delay_t = DelayTime::create(ff);
	auto shootArray = Repeat::create(Sequence::create(delay_t, shoot, nullptr), 10);
	
	if (isEnemy && targetPos.x - attackPos.x > 0)
	{
		myHero->setFlippedX(!isFliped);
		isFliped = (!isFliped);
	}
	else if (!isEnemy && targetPos.x - attackPos.x < 0)
	{
		myHero->setFlippedX(!isFliped);
		isFliped = (!isFliped);
	}
	
	if (!stay)
	{
		auto move = MoveTo::create(moveDuration, attackPos);
		auto shootDelay = DelayTime::create(moveDuration);
		auto delayedShoot = Sequence::create(shootDelay, shootArray, nullptr);
		delayedShoot->setTag(TAG_ACTION_SHOOT);
		myHero->runAction(move);
		myHero->runAction(delayedShoot);
	}
	else
	{
		shootArray->setTag(TAG_ACTION_SHOOT);
		myHero->runAction(shootArray);
	}
}