#include "HeroActor.h"

bool HeroActor::init()
{
	if (!Node::init())
	{
		return true;
	}

	return true;
}

HeroActor::HeroActor()
{
	//empty
}

HeroActor:: ~HeroActor()
{
	//empty
}

void HeroActor::setHeroPos(const Vec2& pos)
{
	myHero->setPosition(pos);
	bloodBar->setPosition((pos + offset));
}
Vec2 HeroActor::getHeroPos() const
{
	return (myHero->getPosition());
}
Size HeroActor::getHeroSize() const
{
	return (myHero->getContentSize());
}
Vec2 HeroActor::getHeroStayPos()const
{
	return attackPos;
}


void HeroActor::lockedSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest)
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

void HeroActor::setBoardPos(const int x, const int y)
{
	this->boardX = x;
	this->boardY = y;
}
std::pair<int, int>HeroActor::getBoardPos()const
{
	return std::make_pair(boardX, boardY);
}
std::pair<int, int>HeroActor::getTargetBoardPos()const
{
	return std::make_pair(targetBoardPosX, targetBoardPosY);
}
void HeroActor::setAlive(bool is)
{
	isAlive = is;
}

void  HeroActor::update()
{
	if (m_Star == 1)
		bloodBar->setPosition((myHero->getPosition() + offset));
	else
		bloodBar->setPosition((myHero->getPosition() + offset * STARS_UP));
	if (isAlive)
	{
		if (m_Star == 1)
			bloodBar->setPercentage(static_cast<float>(this->m_HP) / HeroHp[m_Type] * 100.f);
		else
			bloodBar->setPercentage(static_cast<float>(this->m_HP) / (HeroHp[m_Type] * STARS_UP) * 100.f);
	}
	else
		bloodBar->setPercentage(0);
}

void HeroActor::setHeroOpacity(const uint8_t p)
{
	myHero->setOpacity(p);
	bloodBar->setOpacity(p);
}
void HeroActor::setOrientation(const int orit)
{
	//Ä¬ÈÏ³¯Ïò ÓÒ
	//Ä¬ÈÏsetFlip(true) ¾µÏñ setFlip(false) È¡Ïû¾µÏñ
	if (TO_RIGHT == orit)
	{
		myHero->setFlippedX(false);
	}
	else if (TO_LEFT == orit)
	{
		myHero->setFlippedX(true);
	}
}

void HeroActor::stopShootAndMove()
{
	myHero->stopAllActions();
}
void HeroActor::stopHeroActionByTag(const int actionTag)
{
	myHero->stopActionByTag(actionTag);
}

void HeroActor::selfDied()
{
	setHeroOpacity(0);
	stopShootAndMove();
	dieOnce = true;
}
void HeroActor::enemyDied()
{
	stopHeroActionByTag(TAG_ACTION_SHOOT);
	isTargetAlive = false;
}

void HeroActor::resetHero()
{
	isAlive = true;
	isTargetAlive = true;
	dieOnce = false;
	if(m_Star==1)
		m_HP = static_cast<unsigned int>(HeroHp[m_Type]);
	else
		m_HP = static_cast<unsigned int>(HeroHp[m_Type] * STARS_UP);
	myHero->setFlippedX(isEnemy);
	resetHeroTag();
	setHeroOpacity(255);
	bloodBar->setPercentage(100.f);
	stopShootAndMove();
	auto animate = createAnimate("attack");
	myHero->runAction(animate);
}

void HeroActor::getEnemy(const std::vector<Vec2>& vec)
{
	vecPos = vec;
}

void HeroActor::getDamaged(const DAMAGE& bulletDamage)
{
	int realDamage = 0;

	int physicDamage = bulletDamage.m_PhysicalDamage - this->m_Status.m_Defense.m_PhysicalDefense;
	int powerDamage = bulletDamage.m_PowerDamage - this->m_Status.m_Defense.m_PowerDefense;

	realDamage = (physicDamage > 0 ? physicDamage : 0) +
		(powerDamage > 0 ? powerDamage : 0);

	if (realDamage < 0)
	{
		realDamage = 0;
	}
	if (this->m_HP > static_cast<unsigned int>(realDamage))
		this->m_HP -= static_cast<unsigned int>(realDamage);
	else
	{
		this->m_HP = 0;
		this->isAlive = false;
	}
}

void HeroActor::createHeroActor(const bool enemy)
{
	isEnemy = enemy;
	myHero = Sprite::create(heroPic[m_Type]);
	myHero->setScale(HERO_SCALE);
	myHero->setFlippedX(isEnemy);
	this->addChild(myHero);
	Sprite* bloodSp = nullptr;
	if (!enemy)
	{
		bloodSp = Sprite::create("blood.png");
	}
	else
	{
		bloodSp = Sprite::create("bloodEnemy.png");
	}
	bloodSp->setTag(1000);
	bloodBar = ProgressTimer::create(bloodSp);
	bloodBar->setType(ProgressTimer::Type::BAR);
	bloodBar->setMidpoint(Point(0, 0.5));
	bloodBar->setBarChangeRate(Point(1, 0));
	bloodBar->setPercentage(100.f);
	bloodBar->setScale(BLOODBAR_SCALE);

	addChild(bloodBar);

	auto animate = createAnimate("attack");
	myHero->runAction(animate);
}

void HeroActor::heroBuild()
{
	m_Tag = isEnemy ? TAG_AISIDE : TAG_MYSIDE;
	myHero->setTag(isEnemy ? TAG_AISIDE : TAG_MYSIDE);
	auto playerPhysic = PhysicsBody::createEdgeBox((myHero->getContentSize()) * 0.5f);
	playerPhysic->setDynamic(false);
	playerPhysic->setCategoryBitmask(isEnemy ? AI_HERO_CATGORY_BITMASK : MY_HERO_CATGORY_BITMASK);
	playerPhysic->setContactTestBitmask(isEnemy ? AI_HERO_CONTACT_BITMASK : MY_HERO_CONTACT_BITMASK);
	myHero->setPhysicsBody(playerPhysic);
}

void HeroActor::changeHeroTag(const int t)
{
	myHero->setTag(t);
}

void HeroActor::resetHeroTag()
{
	myHero->setTag(m_Tag);
}

void HeroActor::starsUP()
{
	m_Star++;
	m_Status *= STARS_UP;
	myHero->setScale(HERO_SCALE * STARS_UP);
}

Animate* HeroActor::createAnimate(const char* action)
{
	int num = 0;
	if (action == "attack")
	{
		num = attackPicNum[m_Type];
	}
	else
	{
		num = runPicNum[m_Type];
	}

	Animation* animation = Animation::create();
	SpriteFrame* frame = nullptr;
	for (int i = 1; i <= num; i++)
	{
		std::string mmm = StringUtils::format("chess_action/chess%d/%s/chess%d_%s%d.png",
			                                   m_Type + 1, action, m_Type + 1, action, i);
		frame = SpriteFrame::create(mmm, Rect(0, 0, 98, 98));
		animation->addSpriteFrame(frame);
	}

	animation->setLoops(-1);
	animation->setDelayPerUnit(1.0f / num);
	Animate* animate = Animate::create(animation);
	if (action == "attack")
	{
		animate->setTag(TAG_ACTION_ATTACK);
	}
	else
	{
		animate->setTag(TAG_ACTION_RUN);
	}
	
	animate->retain();
	return animate;
}

void HeroActor::doAttack()
{
}

void HeroActor::doStand()
{
}

void HeroActor::addBuff(const std::string& equipmentName)
{ 
	STATUS buff, buffedStatus;
	if (equipmentName == "physicBuff.png")
	{
		buff = physicBuff;
	}
	else if (equipmentName == "powerBuff.png")
	{
		buff = powerBuff;
	}
	else if (equipmentName == "frequencyBuff.png")
	{
		buff = frequencyBuff;
	}
	else if (equipmentName == "allBuff.png")
	{
		buff = allBuff;
	}
	buffedStatus = this->m_Status + buff;
	this->m_Status = buffedStatus;
}