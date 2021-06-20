#include "Server.h"



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
BOOL Server::OpenTCPServer(_In_ unsigned long block)
{
	BOOL bRet = FALSE;
	WSADATA wsaData = { 0 };
	SOCKADDR_IN ServerAddr = { 0 };
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = 18000;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	do
	{
		if (!WSAStartup(MAKEWORD(2, 2), &wsaData))
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
			if (dwError == WSAEWOULDBLOCK)  //还没收到连接请求
				Sleep(100);
		}
	} while (sClient == INVALID_SOCKET);
	return TRUE;
}