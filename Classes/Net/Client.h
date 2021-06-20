#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "cocos2d.h"

USING_NS_CC;


class Client
{
public:
	Client();
	~Client();
	BOOL InitSocket(_In_ unsigned long block);
	BOOL ConnectServer();
	//获得我的SOCKET
	SOCKET* GetMySOCKET() ;

private:
	SOCKET sClient;
	SOCKADDR_IN addrServer;
	DWORD dwError;
		

};




#endif //_CLIENT_H_
#pragma once
