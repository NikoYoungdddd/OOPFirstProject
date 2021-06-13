#ifndef __CONST_H__
#define __CONST_H__

#include<string>
#include"cocos2d.h"
#include"Structs.h"
USING_NS_CC;

#define SPEED 500.f
#define ATTACK_DURATION_MARK 10.f
#define HERO_SCALE 1.f
#define HERO_SCALE_IN_PURCHASE 0.3f
#define BLOODBAR_SCALE 0.6f
#define EQUIPMENT_SCALE 0.3f

#define TAG_ACTION_SHOOT 999
#define TAG_ACTION_RUN 888
#define TAG_ACTION_ATTACK 777

//const enum { EMPTY, OCCUPIED, LOCKED };
#define EMPTY 0
#define OCCUPIED 1
#define LOCKED 2
#define BOARD_PIECE_SIZE 98.f


//更高级的 ai ,暂时没能力实现
#define LOCKED_BY_TANK 3
#define LOCKED_BY_ASSASION 4
#define LOCKED_BY_ADC 5
#define LOCKED_BY_AOE 6
#define LOCKED_BY_AP  7

#define TAG_MYSIDE 100
#define TAG_AISIDE 200

#define MY_HERO_CATGORY_BITMASK  5
#define MY_HERO_CONTACT_BITMASK  1
#define AI_HERO_CATGORY_BITMASK  3
#define AI_HERO_CONTACT_BITMASK  1

#define TAG_MY_BULLET 10
#define TAG_AI_BULLET 20

#define MY_BULLET_CATGORY_BITMASK  5
#define MY_BULLET_CONTACT_BITMASK  2
#define AI_BULLET_CATGORY_BITMASK  3
#define AI_BULLET_CONTACT_BITMASK  4

//血条相对位置
const Vec2 offset = Vec2(0.f, 45.f);

const enum HeroType
{
	Type_Tank, Type_Assasion, Type_ADC, Type_AP, Type_AOE
};

const int TankSearch[8][2]{ {-1,0},{-1,-1},{-1,1},{0,1},{0,-1},{1,0} ,{1,1},{1,-1} };
const int ADCSearch[10][2]{ {-2,0},{-2,-1},{-2,1},{0,2},{0,-2},{-1,0},{-1,-1},{-1,1},{0,1},{0,-1} };
const int AssasionSearch[5][2]{ {1,0},{1,-1},{1,1},{0,1},{0,-1} };
const int AOESearch[8][2]{ {-1,0},{-1,-1},{-1,1},{0,1},{0,-1},{1,0} ,{1,1},{1,-1} };
const int APSearch[10][2]{ {-2,0},{-2,-1},{-2,1},{0,2},{0,-2},{-1,0},{-1,-1},{-1,1},{0,1},{0,-1} };
const float HeroHp[5]{ 3000.f, 2100.f,2400.f,2400.f,2100.f };

const std::string heroPic[5]{ "chess_pic/chess1.png",
							  "chess_pic/chess2.png",
							  "chess_pic/chess3.png",
							  "chess_pic/chess4.png",
							  "chess_pic/chess5.png" };
const int runPicNum[5]{ 3,3,2,5,4 };
const int attackPicNum[5]{ 8,3,5,6,5 };

const float heroBulletScale[5]{0.4f,0.3f,0.3f,0.5f,0.2f};

const std::string heroBulletName[5]{"bullet/Tankbullet.png","bullet/Assasionbullet.png" ,"bullet/ADCbullet.png",
									"bullet/APbullet.png" ,"bullet/AOEbullet.png" };
const std::string heroName[5]{ "Tank.png","Assasion.png","ADC.png","AP.png","AOE.png" };
const std::string weaponName[4]{ "buff/physicBuff.png","buff/powerBuff.png","buff/frequencyBuff.png","buff/allBuff.png" };
const float putPos[5] = { 3.f,2.4f,2.f,1.7f,1.5f };

const STATUS powerBuff(50, 0, 0, 100, 0);
const STATUS physicBuff(0, 50, 100, 0, 0);
const STATUS frequencyBuff(0, 0, 0, 0, 2);
const STATUS allBuff(40, 40, 40, 40, 1);


//音乐
#define BGM "music/bgm_1.mp3"
#define BGM_pressed "music/pressed.mp3"
#define BGM_game "music/bgm_game.mp3"
//图标,注意下面3张在startscene,startgame的cpp里面有problemloading改不了
#define CLOSE_BUTTON "closeItem.png"
#define START_BUTTON "startItem.png"
#define START_BACKGROUND "startBg.png"
#define CHESS_PURCHASE "ChessSelected.png"
#define PURCHASE_BACKGROUND "purchaseBg.png"
//标题
#define TITLE "Enjoy autochess!"
//地图
#define MAP "chessboard3.tmx"


#endif
