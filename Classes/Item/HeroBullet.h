#ifndef __HEROBULLET_H__
#define __HEROBULLET_H__

#include"Const/Const.h"

class HeroBullet :public Node
{

public:

	HeroBullet(const std::string& bulletName, const DAMAGE& bulletDamage);

	virtual bool init();

	static HeroBullet* create(const std::string& bulletName, const DAMAGE& bulletDamage);
	
	//������������
	void bulletBuild(bool isEnemy, bool second = false);

	//�������ڵ����úͻ�ò���
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

