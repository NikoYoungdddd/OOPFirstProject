#include"HeroBullet.h"

HeroBullet::HeroBullet(const std::string& bulletName, const DAMAGE& bulletDamage)
{
	m_Damage = bulletDamage;
	m_Bullet = Sprite::create(bulletName);
	this->addChild(m_Bullet);
}
bool HeroBullet::init()
{
	if (!Node::init())
	{
		return true;
	}

	return true;
}

HeroBullet* HeroBullet::create(const std::string& bulletName, const DAMAGE& bulletDamage)
{
	auto pRet = new HeroBullet(bulletName, bulletDamage);
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
DAMAGE HeroBullet::getBulletDamage()const
{
	return this->m_Damage;
}
void HeroBullet::setBulletPos(const Vec2& pos)
{
	m_Bullet->setPosition(pos);
}
Vec2 HeroBullet::getBulletPos() const
{
	return m_Bullet->getPosition();
}
void HeroBullet::setBulletScale(float s)
{
	m_Bullet->setScale(s);
}

void HeroBullet::bulletBuild(bool isEnemy,bool isSecond)
{
	if (isSecond)
		m_Bullet->setTag(isEnemy ? TAG_AI_SECOND_BULLET : TAG_MY_SECOND_BULLET);
	else
		m_Bullet->setTag(isEnemy ? TAG_AI_BULLET : TAG_MY_BULLET);
	auto bulletSize = m_Bullet->getContentSize();
	auto bulletPhysic = PhysicsBody::createEdgeBox(Size(bulletSize.width * 0.08f, bulletSize.height * 0.01f));
	bulletPhysic->setDynamic(false);
	bulletPhysic->setCategoryBitmask(isEnemy ? AI_BULLET_CATGORY_BITMASK : MY_BULLET_CATGORY_BITMASK);
	bulletPhysic->setContactTestBitmask(isEnemy ? AI_BULLET_CONTACT_BITMASK : MY_BULLET_CONTACT_BITMASK);
	m_Bullet->setPhysicsBody(bulletPhysic);
}

void HeroBullet::shootBullet(cocos2d::Action* acton)
{
	m_Bullet->runAction(acton);
}


void HeroBullet::setBulletRotation(const Vec2& targetPos)
{
	auto bulletPos = m_Bullet->getPosition();
	auto offset = bulletPos - targetPos;

	float angle;
	if (fabs(offset.x) < 0.0001)
	{
		if (offset.y > 0.0001)
		{
			angle = 90.f;
		}
		else
		{
			angle = -90.f;
		}
	}
	else
	{
		angle = static_cast<float>(-atan(offset.y / offset.x) * 180.f / M_PI);
		if (offset.x > 0.0001)
		{
			angle += 180.f;
		}
	}
	m_Bullet->setRotation(angle);
}
