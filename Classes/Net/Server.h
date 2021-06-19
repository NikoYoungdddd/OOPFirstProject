#ifndef _SERVER_H_
#define _SERVER_H_



#include "cocos2d.h"
#include "Const/Const.h"
USING_NS_CC;

class Server
{
public:
	static Server* getInstance();
	BOOL OpenTCPServer(unsigned long block);
	BOOL AcceptClient();
	SOCKET* GetMySOCKET();

	int SendData(const std::string a, int iSize);
	int RecvDataAndJudge();

	bool isEnemyEnd();
	std::string getEnemyData();
	std::string getMessage();

	bool isMessageDisplayed;
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