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
	//����
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

	//���װ��buff
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
	int m_Type;  //�������ͣ������ഴ��ʱȷ��
	bool isAlive = true;  //�����Ƿ���
	bool isTargetAlive = true;  //�����Ķ����Ƿ����enemyDied����
	bool dieOnce = false;  //�����Ƿ���������selfDied�е���

	unsigned int m_HP;  //Ѫ��
	STATUS m_Status;   //״̬
	unsigned int m_Cost;  //�۸�	
	unsigned int m_Star;
protected:
	std::vector<Vec2> vecPos;  //���˵�λ��
	Sprite* myHero;   //����

	ProgressTimer* bloodBar;  //Ѫ��
	Vec2 targetPos;   //����Ŀ��
	Vec2 targetPos2;  //AOE����������ӵ�����ʱ��ʵ�֣�
	Vec2 attackPos;   //�ڴ�λ�÷����ӵ�
	float moveDuration;  //�ƶ�ʱ��
	bool isEnemy = false;  //�Ƿ�ΪAI����
	
	int boardX, boardY; //�����ϵ�λ��
	int targetBoardPosX, targetBoardPosY;
};
#endif
