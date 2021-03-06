#ifndef __CONST_H__
#define __CONST_H__

#include"cocos2d.h"
#include"Structs.hpp"
USING_NS_CC;


#define PREPARE_TIME 15
#define ROUND_END_TIME 5.f
#define ROUND_TIME 60//6.16号更改过

#define MAX_PLAYER_HP 20
#define STARS_UP 1.2f
#define MAX_BUFF_NUM 5

#define SPEED 500.f
#define ATTACK_DURATION_MARK 25.f
#define HERO_SCALE 1.f
#define HERO_TOUCH_SIZE 0.5f
#define HERO_SCALE_IN_PURCHASE 0.3f
#define GOLD_SCALE_IN_PURCHASE 0.9f
#define UPGRADE_SCALE_IN_GAMESCENE 0.8f
#define BLOODBAR_SCALE 0.6f
#define EQUIPMENT_SCALE 0.22f//此处为了符合装备栏大小改了

#define TAG_ACTION_SHOOT 999
#define TAG_ACTION_RUN 888
#define TAG_ACTION_ATTACK 777

#define EMPTY 0
#define OCCUPIED 12345   //足够大的数（其实大于五就可以了）
#define LOCKED 1  //大于一为被锁定，数字代表被多少Actor锁定
#define BOARD_PIECE_SIZE 98.f

#define TO_RIGHT 1  //图片面朝右
#define TO_LEFT  0  //朝左

#define TAG_MYSIDE 100
#define TAG_AISIDE 200
#define TAG_UNATTACKED 0

#define MY_HERO_CATGORY_BITMASK  5
#define MY_HERO_CONTACT_BITMASK  1
#define AI_HERO_CATGORY_BITMASK  3
#define AI_HERO_CONTACT_BITMASK  1

#define TAG_MY_BULLET 10
#define TAG_AI_BULLET 20
#define TAG_MY_SECOND_BULLET 30
#define TAG_AI_SECOND_BULLET 40

#define MY_BULLET_CATGORY_BITMASK  5
#define MY_BULLET_CONTACT_BITMASK  2
#define AI_BULLET_CATGORY_BITMASK  3
#define AI_BULLET_CONTACT_BITMASK  4

//音乐
#define BGM_START "music/BGMStart.mp3"
#define BGM_ATTACK "music/BGMBattle.mp3"
#define BGM_GAME "music/BGMGame.mp3"

//button
#define CHAT_BG "windows/chatBg.png"
#define CHAT_FR "windows/chatFrame.png"
#define START_BUTTON "button/startItem.png"
#define CLOSE_BUTTON "button/closeItem.png"
#define MUSIC_BUTTON_BACKGROUND "button/musicItemBg.png"
#define MUSIC_BUTTON_CONTENT "button/musicItemContent.png"
#define EXIT_BUTTON "button/yesItem.png"
#define RETURN_BUTTON "button/noItem.png"
#define ENDGAME_BUTTON "button/endItem.png"
#define CHOOSE_AI_BUTTON "button/AIItem.png"
#define CHOOSE_SERVER_BUTTON "button/serverItem.png"
#define CHOOSE_CLIENT_BUTTON "button/clientItem.png"
#define CHESS_PURCHASE_BUTTON "button/ChessSelected.png"
#define SEND_BUTTON "button/chatSendItem.png"
#define UPGRADE_BUTTON "button/upgradeItem.png"

//background
#define START_BACKGROUND "background/startBg.png"
#define PURCHASE_BACKGROUND "background/purchaseBg.png"
#define UNCLEAR_MAP "background/unclearMap.png"
#define UNCLEAR_BACKGROUND "background/unclearstartBg.png"

//windows
#define PLAYER_WINDOW "windows/playerWindow.png"
#define ENEMY_WINDOW "windows/enemyWindow.png"
#define WIN_FLAG "windows/win.png"
#define LOSE_FLAG "windows/lose.png"
#define DRAW_FLAG "windows/draw.png"
#define ENDGAME_WIN_WINDOW "windows/endWinWindow.png"
#define ENDGAME_DRAW_WINDOW "windows/endDrawWindow.png"
#define ENDGAME_LOSE_WINDOW "windows/endLoseWindow.png"

//其它
#define GOLD "gold.png"

//地图
#define MAP "chessboard3.tmx"

//联机
#define MAXBUF 99
#define SERVER 0
#define CLIENT 1


//血条、蓝条相对位置
static const Vec2 offset = Vec2(0.f, 46.f);
static const Vec2 offset2 = Vec2(0.f, 43.f);

const enum HeroType
{
	Type_Tank, Type_Assasion, Type_ADC, Type_AP, Type_AOE
};

static const int TankSearch[8][2]{ {-1,0},{-1,-1},{-1,1},{0,1},{0,-1},{1,0} ,{1,1},{1,-1} };
static const int ADCSearch[10][2]{ {-2,0},{-2,-1},{-2,1},{0,2},{0,-2},{-1,0},{-1,-1},{-1,1},{0,1},{0,-1} };
static const int AssasionSearch[5][2]{ {1,0},{1,-1},{1,1},{0,1},{0,-1} };
static const int AOESearch[8][2]{ {-1,0},{-1,-1},{-1,1},{0,1},{0,-1},{1,0} ,{1,1},{1,-1} };
static const int APSearch[10][2]{ {-2,0},{-2,-1},{-2,1},{0,2},{0,-2},{-1,0},{-1,-1},{-1,1},{0,1},{0,-1} };
static const float HeroHp[5]{ 3000.f, 2100.f,2400.f,2400.f,2100.f };
static const float maxDistance[5] = { 200.f,200.f,300.f,300.f,300.f };

static const int runPicNum[5]{ 3,3,2,5,4 };
static const int attackPicNum[5]{ 8,3,5,6,5 };
static const float heroBulletScale[5]{ 0.4f,0.3f,0.3f,0.5f,0.2f };
static const float putPos[5] = { 3.f,2.4f,2.f,1.7f,1.5f };
static const int heroPrice[5]{ 1,1,3,2,3 };
static const int playerExpPerGrade[5] = { 1,3,6,9,15 };

//防御 物理 法术
//攻击 物理 法术
//频率
static const STATUS powerBuff(50, 0, 0, 150, 0);
static const STATUS physicBuff(0, 50, 150, 0, 0);
static const STATUS frequencyBuff(0, 0, 0, 0, 30);
static const STATUS allBuff(50, 50, 100, 100, 10);

static const STATUS TankSkill(0, 0, 50, 50, 0);
static const STATUS AssasionSkill(50, 50, 0, 0, 0);
static const STATUS ADCSkill(50, 0, 0, 50, 0);
static const STATUS APSkill(0, 0, 0, 0, 20);
static const STATUS AOESkill(0, 50, 50, 0, 0);
static const STATUS heroSkill[5]{ TankSkill , AssasionSkill , ADCSkill,APSkill,AOESkill };

static const int skillMP[5]{ 3,10,5,5,5 };


static const std::string heroPic[5]{ "chess_pic/chess1.png",
									 "chess_pic/chess2.png",
									 "chess_pic/chess3.png",
									 "chess_pic/chess4.png",
									 "chess_pic/chess5.png" };
static const std::string heroBulletName[5]{ "bullet/Tankbullet.png","bullet/Assasionbullet.png" ,"bullet/ADCbullet.png",
									"bullet/APbullet.png" ,"bullet/AOEbullet.png" };
static const std::string heroName[5]{ "Tank.png","Assasion.png","ADC.png","AP.png","AOE.png" };
static const std::string weaponName[4]{ "buff/physicBuff.png","buff/powerBuff.png","buff/frequencyBuff.png","buff/allBuff.png" };

#endif
