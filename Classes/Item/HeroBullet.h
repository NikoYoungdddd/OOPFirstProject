#ifndef __HEROBULLET_H__
#define __HEROBULLET_H__

#include"Const/Const.h"

class HeroBullet :public Node
{

public:

	HeroBullet(const std::string& bulletName, const DAMAGE& bulletDamage);

	virtual bool init();

	static HeroBullet* create(const std::string& bulletName, const DAMAGE& bulletDamage);
	
	//设置物理引擎
	void bulletBuild(bool isEnemy, bool second = false);

	//在其他节点设置和获得参数
	void setBulletPos(const Vec2& pos);	
	
	void setBulletScale(const float s);	
	
	void shootBullet(Action* acton);
	
	void setBulletRotation(const Vec2& targetPos);
	
	DAMAGE getBulletDamage()const;

protected:
	Sprite* m_Bullet;
	DAMAGE m_Damage;
};
#endif

