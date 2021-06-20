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
	addrServer.sin_family = AF_INET;      //����server��ַ
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
	int iRemain = iSize;  //ʣ���ֽ�
	int iCur = 0;         //��ǰ���͵��ֽ�
	int iLen = 0;
	while (iRemain)
	{
		iLen = send(sClient, &p[iCur], iSize, 0);
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
	log("send: ");
	log(p);
	return iCur;
}


int Client::RecvDataAndJudge()
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
	return iCur;//���ؽ����˵ĳ���
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