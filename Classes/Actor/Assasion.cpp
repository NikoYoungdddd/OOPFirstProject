#include "Assasion.h"
//        HeroAssasion
Assasion::Assasion()
{
	this->m_HP = 2100;
	this->m_Status.m_Damage.m_PhysicalDamage = 200;
	this->m_Status.m_Damage.m_PowerDamage = 50;
	this->m_Status.m_Defense.m_PhysicalDefense = 70;
	this->m_Status.m_Defense.m_PowerDefense = 50;
	this->m_Status.m_AttackFrequency = 5;
	this->m_Cost = 1;
	this->m_Type = Type_Assasion;
	boardX = -1;
	boardY = -1;
}



void Assasion::searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay)
{
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 startDest = myHero->getPosition();
	Vec2 endDest = *(vecPos.begin());
	Vec2 stayPos = startDest;
	float longestLen = sqrt((startDest.x - endDest.x) * (startDest.x - endDest.x) +
		(startDest.y - endDest.y) * (startDest.y - endDest.y));

	for (auto i : vecPos)
	{
		auto tempDest = i;
		float len = sqrt((startDest.x - tempDest.x) * (startDest.x - tempDest.x) +
			(startDest.y - tempDest.y) * (startDest.y - tempDest.y));
		if (!stay)
		{
			if (len > longestLen)
			{
				longestLen = len;
				endDest = tempDest;
			}
		}
		else
		{
			if (len < longestLen)
			{
				longestLen = len;
				endDest = tempDest;
			}
		}
	}


	if (!stay)
	{
		int flag = 1;
		board[boardX][boardY].second = EMPTY;

		for (int i = 0; i < 8 && flag; i++)
		{
			for (int j = 0; j < 8 && flag; j++)
			{
				if (board[i][j].first == endDest)
				{
					targetBoardPosX = i;
					targetBoardPosY = j;
					if (board[i][j].second == OCCUPIED)
						board[i][j].second = EMPTY;
					board[i][j].second ++;
					for (int k = 0; k < 5; k++)
					{
						int x = AssasionSearch[k][0], y = AssasionSearch[k][1];
						if (i + x < 0 || i + x >= 8 || i + y < 0 || i + y >= 8)
							continue;
						if (!board[i + x][j + y].second)
						{
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
	
	}

	else
	{
		int flag = 1;
		for (int i = 0; i < 8 && flag; i++)
		{
			for (int j = 0; j < 8 && flag; j++)
			{
				if (board[i][j].first == endDest)
				{
					targetBoardPosX = i;
					targetBoardPosY = j;
					if (board[i][j].second == OCCUPIED)
						board[i][j].second = EMPTY;
					board[i][j].second++;
					flag = 0;
				}
			}
		}
	}
	targetPos = endDest;
	attackPos = stayPos;
	moveDuration = longestLen / SPEED;
}

void Assasion::attack(const bool stay)
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
	auto shootArray = Repeat::create(Sequence::create(delay_t, shoot, nullptr), 20);	
	//auto shootArray = RepeatForever::create(Sequence::create(delay_t, shoot, nullptr));

	if (targetPos.x - attackPos.x > 0.00001f)
	{
		this->setOrientation(TO_RIGHT);
	}
	else if (targetPos.x - attackPos.x < -0.00001f)
	{
		this->setOrientation(TO_LEFT);
	}
	if (!stay)
	{
		auto jump = JumpTo::create(moveDuration, attackPos, 100, 3);
		auto shootDelay = DelayTime::create(moveDuration);
		auto delayedShoot = Sequence::create(shootDelay, shootArray, nullptr);
		delayedShoot->setTag(TAG_ACTION_SHOOT);
		myHero->runAction(jump);
		myHero->runAction(delayedShoot);
	}
	else
	{
		shootArray->setTag(TAG_ACTION_SHOOT);
		myHero->runAction(shootArray);
	}
}