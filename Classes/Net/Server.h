#ifndef _SERVER_H_
#define _SERVER_H_



#include "cocos2d.h"

USING_NS_CC;

class Server
{
public:
	Server();
	~Server();
	BOOL OpenTCPServer(unsigned long block);
	BOOL AcceptClient();
private:
	SOCKET sServer;
	SOCKET sClient;
	DWORD dwError;
	SOCKADDR ClientAddr;


};



















#endif
#pragma once
