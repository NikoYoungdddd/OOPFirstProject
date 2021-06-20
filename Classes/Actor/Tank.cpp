#include "Tank.h"

Tank::Tank()
{

	this->m_HP = 2800;
	this->m_Status.m_Damage.m_PhysicalDamage = 150;
	this->m_Status.m_Damage.m_PowerDamage = 0;
	this->m_Status.m_Defense.m_PhysicalDefense = 50;
	this->m_Status.m_Defense.m_PowerDefense = 0;
	this->m_Status.m_AttackFrequency = 30;
	this->m_Cost = 1;
	this->m_Type = Type_Tank;
	this->m_Star = 1;

	boardX = -1;
	boardY = -1;
}

void Tank::moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos)
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
				board[i][j].second++;
				for (int k = 0; k < 8; k++)
				{
					int x = TankSearch[k][0], y = TankSearch[k][1];
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


void Tank::searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay)
{
	Vec2 startDest = myHero->getPosition();
	Vec2 endDest = *(vecPos.begin());
	Vec2 stayPos = startDest;
	float shortestLen = sqrt((startDest.x - endDest.x) * (startDest.x - endDest.x) +
		(startDest.y - endDest.y) * (startDest.y - endDest.y));

	for (auto i : vecPos)
	{
		auto tempDest = i;
		float len = sqrt((startDest.x - tempDest.x) * (startDest.x - tempDest.x) +
			(startDest.y - tempDest.y) * (startDest.y - tempDest.y));
		if (len < shortestLen)
		{
			shortestLen = len;
			endDest = tempDest;
		}
	}

	if (!stay)
	{
		moveSearch(board, endDest, stayPos);
	}
	else
	{
		lockedSearch(board, endDest);
	}

	targetPos = endDest;
	attackPos = stayPos;
	moveDuration = shortestLen / SPEED;
}


void Tank::attack(const bool stay)
{
	float ff = ATTACK_DURATION_MARK / m_Status.m_AttackFrequency;

	float distance = sqrt((attackPos.x - targetPos.x) * (attackPos.x - targetPos.x)
		+ (attackPos.y - targetPos.y) * (attackPos.y - targetPos.y));

	int dampdeRate = 1;
	if (distance > maxDistance[m_Type])
		dampdeRate++;
	auto shoot = CallFunc::create([=]() {
		auto attackBullet = HeroBullet::create(heroBulletName[m_Type], this->m_Status.m_Damage / dampdeRate);
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
	auto shootArray = Repeat::create(Sequence::create(delay_t, shoot, nullptr), 50);

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
		auto move = MoveTo::create(moveDuration, attackPos);
		auto shootDelay = DelayTime::create(moveDuration);
		auto delayedShoot = Sequence::create(shootDelay, shootArray, nullptr);
		delayedShoot->setTag(TAG_ACTION_SHOOT);
		myHero->runAction(move);
		stopAnimation(TAG_ACTION_RUN);
		startAniamtion("attack");
		myHero->runAction(delayedShoot);
	}
	else
	{
		stopAnimation(TAG_ACTION_RUN);
		startAniamtion("attack");
		shootArray->setTag(TAG_ACTION_SHOOT);
		myHero->runAction(shootArray);
	}
}

