#ifndef __HEROACTOR_H__
#define __HEROACTOR_H__

#include"Const/Const.h"
#include"Item/HeroBullet.h"

class HeroActor :public Node
{

public:

	HeroActor();

	~HeroActor();

	virtual bool init();

	virtual void createHeroActor(const bool enemy = false);

	//添加物理引擎
	virtual void heroBuild();

	//被攻击
	virtual void getDamaged(const DAMAGE& bulletDamage);

	//索敌
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false) = 0;

	//未被锁定时的索敌
	virtual void moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos) = 0;

	//被锁定时的索敌
	virtual void lockedSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest);

	//移动攻击
	virtual void attack(const bool stay = false) = 0;
	//技能
	virtual void skill();

	//从其他节点接收和设置hero的参数
	virtual void setHeroPos(const Vec2& pos);
	
	virtual Vec2 getHeroPos() const;
	
	virtual Size getHeroSize() const;
	
	virtual	Vec2 getHeroStayPos() const;
	
	virtual void changeHeroTag(const int t);
	
	virtual void resetHeroTag();
	
	virtual void setBoardPos(const int x, const int y);
	
	virtual std::pair<int, int>getBoardPos()const;
	
	virtual std::pair<int, int>getTargetBoardPos()const;

	//获取敌人位置
	virtual void getEnemy(const std::vector<Vec2>& vec);
	
	//设置精灵朝向
	virtual void setOrientation(const int orit);

	//添加装备buff
	virtual void addBuff(const std::string& equipmentName);

	virtual void update();

	//是否存活
	virtual void setAlive(bool is = true);

	//设置所有精灵的透明度
	virtual void setHeroOpacity(const uint8_t p);

	//死亡时停止动作，设置属性
	virtual void stopShootAndMove();
	
	virtual void stopHeroActionByTag(const int actionTag);
	
	virtual void selfDied();
	
	virtual void enemyDied();

	//创建动画、
	virtual Animate* createAnimate(const char* action);
	
	virtual void startAniamtion(const char *action);
	
	virtual void stopAnimation(int tag);
	
	//重置英雄属性
	virtual void resetHero();

	//升星
	virtual void starsUP();

public:
	
	bool isAlive = true;  //本局是否存活
	bool isTargetAlive = true;  //锁定的对象是否存活，在enemyDied调用
	bool dieOnce = false;  //本次是否死亡，在selfDied中调用
	bool isSkilled = false;
	int skillNum = 0;

	unsigned int m_HP;  //血量
	unsigned int m_Tag;   //tag
	int m_Type;  //棋子类型，在子类创建时确定
	STATUS m_Status;   //状态
	unsigned int m_Cost;  //价格	
	unsigned int m_Star;
	int effectiveAttackNum = 0;
	
protected:
	std::vector<Vec2> vecPos;  //敌人的位置
	Sprite* myHero;   //精灵
	ProgressTimer* bloodBar;  //血条
	ProgressTimer* blueBar;
	Vec2 targetPos;   //攻击目标
	Vec2 attackPos;   //在此位置发射子弹
	float moveDuration;  //移动时间
	bool isEnemy = false;  //是否为AI创建

	int boardX, boardY; //棋盘上的位置
	int targetBoardPosX, targetBoardPosY;
};
#endif

