#include "Client.h"


Client::Client()
{
	sClient= INVALID_SOCKET;
	dwError = 0;
	addrServer.sin_family = AF_INET;      //…Ë÷√serverµÿ÷∑
	addrServer.sin_port = 18000;
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
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