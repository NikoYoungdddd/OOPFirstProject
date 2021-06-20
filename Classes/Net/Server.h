#ifndef _SERVER_H_
#define _SERVER_H_


#include "Const/Const.h"


class Server
{
public:
	//单例模式的使用
	static Server* getInstance();
	
	//打开服务器 传入参数0为阻塞 1为非阻塞
	BOOL OpenTCPServer(unsigned long block);
	
	//监听是否有客户端连接函数
	BOOL AcceptClient();
	
	//返回接收到的SOCKET
	SOCKET* GetMySOCKET();
	
	//发送信息函数
	int SendData(const std::string a, int iSize);
	
	//接收来自服务端的信息并判断信息类型
	int RecvDataAndJudge();
	
	//判定是否结束
	bool isEnemyEnd();
	
	//获取敌人信息
	std::string getEnemyData();
	
	//获取当前收到的聊天信息
	std::string getMessage();
	
	//判定聊天信息是否已经被放置在聊天框
	bool isMessageDisplayed;
	
	//储存当前IP
	std::string myIP;

private:
	Server();
	~Server();
	SOCKET sServer;
	SOCKET sClient;
	DWORD dwError;
	SOCKADDR ClientAddr;
	static Server* myServer;

	std::string enemyData;
	std::string message;
	bool isEnemyEnded;

};

#endif