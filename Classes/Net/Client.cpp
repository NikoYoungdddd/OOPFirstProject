#include "Client.h"

Client* Client::myClient = nullptr;


Client* Client::getInstance()
{
	if (myClient == nullptr)
	{
		myClient = new Client();
		return myClient;
	}
	return myClient;

}


Client::Client()
{
	sClient = INVALID_SOCKET;
	dwError = 0;
	addrServer.sin_family = AF_INET;      //设置server地址
	addrServer.sin_port = 18000;


}


BOOL Client::InitSocket(_In_ unsigned long block)
{



	BOOL bRet = FALSE;
	WSADATA wsaData = { 0 };
	do
	{
		if (!WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			if (LOBYTE(wsaData.wVersion) == 2 || HIBYTE(wsaData.wVersion) == 2)
			{
				sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				if (ioctlsocket(sClient, FIONBIO, (unsigned long*)&block) != SOCKET_ERROR)
				{
					if (sClient != INVALID_SOCKET)
					{
						bRet = TRUE;
						break;
					}
					dwError = WSAGetLastError();
				}
				dwError = WSAGetLastError();
			}
		}
		dwError = WSAGetLastError();
	} while (FALSE);
	return bRet;
}


BOOL Client::ConnectServer()
{
	addrServer.sin_addr.S_un.S_addr = inet_addr(myIP.data());
	DWORD DwError = 0;
	while (1)
	{
		if (SOCKET_ERROR == connect(sClient, (SOCKADDR*)&addrServer, sizeof(addrServer)))
		{
			DwError = WSAGetLastError();
			if (DwError == WSAEWOULDBLOCK || dwError == WSAEINVAL)
			{
				Sleep(100);
				continue;
			}
			else if (DwError == WSAEISCONN)
				break;
			else
				return FALSE;
		}
		else
			break;
	}
	return TRUE;
}



SOCKET* Client::GetMySOCKET()
{

	return &sClient;
}


int Client::SendData(const std::string a, _In_ int iSize)
{
	const char* p = a.data();
	int iRemain = iSize;  //剩余字节
	int iCur = 0;         //当前发送的字节
	int iLen = 0;
	while (iRemain)
	{
		iLen = send(sClient, &p[iCur], iSize, 0);
		if (iLen == SOCKET_ERROR)
		{
			DWORD dwError = GetLastError();
			if (dwError == WSAEWOULDBLOCK)
				continue;
			else                  //其它错误
				return -1;
		}
		iCur += iLen;
		iRemain = iSize - iLen;  //求出还剩余多少字节没有发送
	}
	log("send: ");
	log(p);
	return iCur;
}


int Client::RecvDataAndJudge()
{
	char buf[MAXBUF] = { 0 };
	int iSize = MAXBUF;
	int iRemain = iSize;  //剩余字节
	int iCur = 0;         //当前读取到的字节
	int iLen = 0;
	//接收过程
	while (iRemain)
	{
		iLen = recv(sClient, &buf[iCur], iSize, 0);
		if (iLen == SOCKET_ERROR)            //这里不用判断WSAEWOULDBLOCK错误代码
			break;
		iCur += iLen;
		iRemain = iSize - iLen;  //求出还剩余多少字节没有读完
	}

	//开始判断接收到的信息
	std::string bufString(buf);
	if (bufString.size() != 0)
	{
		if (bufString[0] == 'E' && bufString[1] == 'N' && bufString[2] == 'D')
		{
			isEnemyEnded = true;
			enemyData = "";
			log("has recv end");
		}
		else if (bufString[0] == 'm' && bufString[1] == 'e' && bufString[2] == 's')
		{
			message = bufString;
			isMessageDisplayed = false;
			log("has recv message");
		}
		if (bufString[0] > '0' && bufString[0] <= '9')
		{
			isEnemyEnded = false;
			enemyData = bufString;
			log("has recv enemydata");
		}
		log("recv: ");
		log(buf);
	}
	return iCur;//返回接受了的长度
}


bool Client::isEnemyEnd()
{
	return isEnemyEnded;
}


std::string Client::getEnemyData()
{
	return enemyData;
}


std::string Client::getMessage()
{
	return message;
}