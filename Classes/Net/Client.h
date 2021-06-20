#ifndef _CLIENT_H_
#define _CLIENT_H_


#include "Const/Const.h"

class Client
{
public:
	//初始化socket 传入参数0为阻塞  1为非阻塞
	BOOL InitSocket(_In_ unsigned long block);
	
	//尝试连接服务器
	BOOL ConnectServer();
	
	//获得我的SOCKET
	SOCKET* GetMySOCKET();
	
	//发送信息到服务器
	int SendData(const std::string a, int iSize);
	
	//接受信息并判断消息类型 根据消息类型进行处理
	int RecvDataAndJudge();
	
	//单例模式使用
	static Client* getInstance();
	
	//判断服务器端对战是否结束
	bool isEnemyEnd();
	
	//获取服务器端敌人信息
	std::string getEnemyData();
	
	//获取已经接收到的信息
	std::string getMessage();
	
	//用来判定是否已经把收到的信息放置在聊天框
	bool isMessageDisplayed;
	
	//储存当前IP
	std::string myIP;

private:
	Client();
	~Client();
	SOCKET sClient;
	SOCKADDR_IN addrServer;
	DWORD dwError;

	static Client* myClient;
	std::string enemyData;
	std::string message;
	bool isEnemyEnded;

};

#endif 