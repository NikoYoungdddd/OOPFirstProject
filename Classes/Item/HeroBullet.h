#ifndef __HEROBULLET_H__
#define __HEROBULLET_H__

#include"Const/Const.h"

class HeroBullet :public Node
{

public:
	
	HeroBullet(const std::string& bulletName, const DAMAGE& bulletDamage);
	virtual bool init();
	static HeroBullet* create(const std::string& bulletName, const DAMAGE& bulletDamage);
	DAMAGE getBulletDamage()const;
	
	void setBulletPos(const Vec2& pos);
	Vec2 getBulletPos() const;
	void setBulletScale(const float s);
	void bulletBuild(bool isEnemy,bool second=false);
	void shootBullet(cocos2d::Action* acton);
	void setBulletRotation(const Vec2& targetPos);

protected:
	Sprite* m_Bullet;
	DAMAGE m_Damage;
};
#endif
