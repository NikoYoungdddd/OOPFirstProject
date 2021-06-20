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

	//�����������
	virtual void heroBuild();

	//������
	virtual void getDamaged(const DAMAGE& bulletDamage);

	//����
	virtual void searchEnemy(std::pair<Vec2, int>(&board)[8][8], const bool stay = false) = 0;

	//δ������ʱ������
	virtual void moveSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest, Vec2& stayPos) = 0;

	//������ʱ������
	virtual void lockedSearch(std::pair<Vec2, int>(&board)[8][8], const Vec2& endDest);

	//�ƶ�����
	virtual void attack(const bool stay = false) = 0;
	//����
	virtual void skill();

	//�������ڵ���պ�����hero�Ĳ���
	virtual void setHeroPos(const Vec2& pos);
	
	virtual Vec2 getHeroPos() const;
	
	virtual Size getHeroSize() const;
	
	virtual	Vec2 getHeroStayPos() const;
	
	virtual void changeHeroTag(const int t);
	
	virtual void resetHeroTag();
	
	virtual void setBoardPos(const int x, const int y);
	
	virtual std::pair<int, int>getBoardPos()const;
	
	virtual std::pair<int, int>getTargetBoardPos()const;

	//��ȡ����λ��
	virtual void getEnemy(const std::vector<Vec2>& vec);
	
	//���þ��鳯��
	virtual void setOrientation(const int orit);

	//���װ��buff
	virtual void addBuff(const std::string& equipmentName);

	virtual void update();

	//�Ƿ���
	virtual void setAlive(bool is = true);

	//�������о����͸����
	virtual void setHeroOpacity(const uint8_t p);

	//����ʱֹͣ��������������
	virtual void stopShootAndMove();
	
	virtual void stopHeroActionByTag(const int actionTag);
	
	virtual void selfDied();
	
	virtual void enemyDied();

	//����������
	virtual Animate* createAnimate(const char* action);
	
	virtual void startAniamtion(const char *action);
	
	virtual void stopAnimation(int tag);
	
	//����Ӣ������
	virtual void resetHero();

	//����
	virtual void starsUP();

public:
	
	bool isAlive = true;  //�����Ƿ���
	bool isTargetAlive = true;  //�����Ķ����Ƿ����enemyDied����
	bool dieOnce = false;  //�����Ƿ���������selfDied�е���
	bool isSkilled = false;
	int skillNum = 0;

	unsigned int m_HP;  //Ѫ��
	unsigned int m_Tag;   //tag
	int m_Type;  //�������ͣ������ഴ��ʱȷ��
	STATUS m_Status;   //״̬
	unsigned int m_Cost;  //�۸�	
	unsigned int m_Star;
	int effectiveAttackNum = 0;
	
protected:
	std::vector<Vec2> vecPos;  //���˵�λ��
	Sprite* myHero;   //����
	ProgressTimer* bloodBar;  //Ѫ��
	ProgressTimer* blueBar;
	Vec2 targetPos;   //����Ŀ��
	Vec2 attackPos;   //�ڴ�λ�÷����ӵ�
	float moveDuration;  //�ƶ�ʱ��
	bool isEnemy = false;  //�Ƿ�ΪAI����

	int boardX, boardY; //�����ϵ�λ��
	int targetBoardPosX, targetBoardPosY;
};
#endif

