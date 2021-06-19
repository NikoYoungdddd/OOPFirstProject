#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "cocos2d.h"
#include "Const/Const.h"
USING_NS_CC;


class Client
{
public:

	BOOL InitSocket(_In_ unsigned long block);
	BOOL ConnectServer();
	//获得我的SOCKET
	SOCKET* GetMySOCKET();
	int SendData(const std::string a, int iSize);

	int RecvDataAndJudge();

	static Client* getInstance();

	bool isEnemyEnd();
	std::string getEnemyData();
	std::string getMessage();

	bool isMessageDisplayed;

private:
	Client();
	~Client();
	SOCKET sClient;
	SOCKADDR_IN addrServer;
	DWORD dwError;
	static Client* myClient;

	std::string enemyData;
	std::string message;
	bool isEnemyEnded=true;
	

};




#endif //_CLIENT_H_
#pragma once

