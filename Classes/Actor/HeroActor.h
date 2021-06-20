#ifndef __HEROACTOR_H__
#define __HEROACTOR_H__

#include"Const/Const.h"
#include"Item/HeroBullet.h"
USING_NS_CC;

class HeroActor :public Node
{

public:

	HeroActor();

	~HeroActor();

	virtual bool init();

	virtual void createHeroActor(const bool enemy = false);

	virtual void heroBuild();

	virtual void getDamaged(const DAMAGE& bulletDamage);

	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false) = 0;

	virtual void attack(const bool stay = false) = 0;
	//技能
	//virtual void skill() = 0;

	virtual void setHeroPos(const Vec2& pos);
	virtual Vec2 getHeroPos() const;
	virtual Size getHeroSize() const;
	virtual	Vec2 getHeroStayPos() const;
	virtual void changeHeroTag(const int t);
	virtual void resetHeroTag();
	virtual void setBoardPos(const int x, const int y);
	virtual std::pair<int, int>getBoardPos()const;
	virtual std::pair<int, int>getTargetBoardPos()const;
	
	virtual void getEnemy(const std::vector<Vec2>& vec);
	virtual void setOrientation(const int orit);

	//添加装备buff
	virtual void addBuff(const std::string& equipmentName);

	virtual void update();

	virtual void setAlive(bool is = true);

	virtual void setHeroOpacity(const uint8_t p);

	virtual void stopShootAndMove();
	virtual void stopHeroActionByTag(const int actionTag);
	virtual void selfDied();
	virtual void enemyDied();

	virtual Animate* createAnimate(const char* action);

	virtual void doAttack();

	virtual void doStand();

	virtual void resetHero();
	
public:
	unsigned int m_Tag;   //tag
	int m_Type;  //棋子类型，在子类创建时确定
	bool isAlive = true;  //本局是否存活
	bool isTargetAlive = true;  //锁定的对象是否存活，在enemyDied调用
	bool dieOnce = false;  //本次是否死亡，在selfDied中调用

	unsigned int m_HP;  //血量
	STATUS m_Status;   //状态
	unsigned int m_Cost;  //价格	
	unsigned int m_Star;
protected:
	std::vector<Vec2> vecPos;  //敌人的位置
	Sprite* myHero;   //精灵

	ProgressTimer* bloodBar;  //血条
	Vec2 targetPos;   //攻击目标
	Vec2 targetPos2;  //AOE会射出两个子弹（暂时不实现）
	Vec2 attackPos;   //在此位置发射子弹
	float moveDuration;  //移动时间
	bool isEnemy = false;  //是否为AI创建
	
	int boardX, boardY; //棋盘上的位置
	int targetBoardPosX, targetBoardPosY;
};
#endif
