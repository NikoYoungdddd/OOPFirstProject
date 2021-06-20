#include "Server.h"

Server* Server::myServer = nullptr;

Server* Server::getInstance()
{
	if (myServer == nullptr)
	{
		myServer = new Server();
		return myServer;
	}
	return myServer;

}


Server::Server()
{
	sServer = INVALID_SOCKET;
	sClient = INVALID_SOCKET;
	ClientAddr = { 0 };
	dwError = 0;
}

Server::~Server()
{

}

BOOL Server::OpenTCPServer(unsigned long block)
{
	BOOL bRet = FALSE;
	WSADATA wsaData = { 0 };
	SOCKADDR_IN ServerAddr = { 0 };
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = 18000;

	ServerAddr.sin_addr.S_un.S_addr = inet_addr(myIP.data());
	do
	{
		if (!WSAStartup(MAKEWORD(2, 2), &wsaData))//������Ӧ��Socket�⣬Ȼ����ҵ���Socket�⵽��Ӧ�ó����� �ɹ�����0
		{
			if (LOBYTE(wsaData.wVersion) == 2 || HIBYTE(wsaData.wVersion) == 2)
			{
				sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				if (ioctlsocket(sServer, FIONBIO, (unsigned long*)&block) != SOCKET_ERROR)
				{
					if (sServer != INVALID_SOCKET)
					{
						if (SOCKET_ERROR != bind(sServer, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)))
						{
							if (SOCKET_ERROR != listen(sServer, SOMAXCONN))
							{
								bRet = TRUE;
								break;
							}
							dwError = WSAGetLastError();
							closesocket(sServer);
						}
						dwError = WSAGetLastError();
						closesocket(sServer);
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


BOOL Server::AcceptClient()
{
	DWORD dwError = 0;
	int a = sizeof(ClientAddr);
	do
	{
		sClient = accept(sServer, &ClientAddr, &a);
		if (sClient == INVALID_SOCKET)
		{
			dwError = WSAGetLastError();
			if (dwError == WSAEWOULDBLOCK)  //��û�յ���������
				Sleep(100);
		}
	} while (sClient == INVALID_SOCKET);
	return TRUE;
}


SOCKET* Server::GetMySOCKET()
{

	return &sClient;
}


int Server::SendData(const std::string a, _In_ int iSize)
{
	int iRemain = iSize;  //ʣ���ֽ�
	int iCur = 0;         //��ǰ���͵��ֽ�
	int iLen = 0;
	const char* buf = a.data();
	while (iRemain)
	{
		iLen = send(sClient, &buf[iCur], iSize, 0);
		if (iLen == SOCKET_ERROR)
		{
			DWORD dwError = GetLastError();
			if (dwError == WSAEWOULDBLOCK)
				continue;
			else                  //��������
				return -1;
		}
		iCur += iLen;
		iRemain = iSize - iLen;  //�����ʣ������ֽ�û�з���
	}
	log("Send:");
	log(buf);
	return iCur;
}


int Server::RecvDataAndJudge()
{
	char buf[MAXBUF] = { 0 };
	int iSize = MAXBUF;
	int iRemain = iSize;  //ʣ���ֽ�
	int iCur = 0;         //��ǰ��ȡ�����ֽ�
	int iLen = 0;
	//���չ���
	while (iRemain)
	{
		iLen = recv(sClient, &buf[iCur], iSize, 0);
		if (iLen == SOCKET_ERROR)            //���ﲻ���ж�WSAEWOULDBLOCK�������
			break;
		iCur += iLen;
		iRemain = iSize - iLen;  //�����ʣ������ֽ�û�ж���
	}

	//��ʼ�жϽ��յ�����Ϣ
	std::string bufString(buf);
	if (bufString.size() != 0)
	{
		if (bufString[0] == 'E' && bufString[1] == 'N' && bufString[2] == 'D')
		{
			isEnemyEnded = true;
			enemyData = "";
		}
		else if (bufString[0] == 'm' && bufString[1] == 'e' && bufString[2] == 's')
		{
			isMessageDisplayed = false;
			message = bufString;
		}
		if (bufString[0] > '0' && bufString[0] <= '9')
			enemyData = bufString;
		log("Recv:");
		log(buf);
	}
	return iCur;//���ؽ����˵ĳ���
}


bool Server::isEnemyEnd()
{
	return isEnemyEnded;
}


std::string Server::getEnemyData()
{
	return enemyData;
}


std::string Server::getMessage()
{
	return message;
}