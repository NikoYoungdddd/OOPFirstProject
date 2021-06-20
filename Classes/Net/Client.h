#ifndef _CLIENT_H_
#define _CLIENT_H_


#include "Const/Const.h"

class Client
{
public:
	//��ʼ��socket �������0Ϊ����  1Ϊ������
	BOOL InitSocket(_In_ unsigned long block);
	
	//�������ӷ�����
	BOOL ConnectServer();
	
	//����ҵ�SOCKET
	SOCKET* GetMySOCKET();
	
	//������Ϣ��������
	int SendData(const std::string a, int iSize);
	
	//������Ϣ���ж���Ϣ���� ������Ϣ���ͽ��д���
	int RecvDataAndJudge();
	
	//����ģʽʹ��
	static Client* getInstance();
	
	//�жϷ������˶�ս�Ƿ����
	bool isEnemyEnd();
	
	//��ȡ�������˵�����Ϣ
	std::string getEnemyData();
	
	//��ȡ�Ѿ����յ�����Ϣ
	std::string getMessage();
	
	//�����ж��Ƿ��Ѿ����յ�����Ϣ�����������
	bool isMessageDisplayed;
	
	//���浱ǰIP
	std::string myIP;

private:
	Client();
	~Client();
	SOCKET sClient;
	SOCKADDR_IN addrServer;
	DWORD dwError;

	static Client* myClient;
	std::string enemyData;
	std::string message;
	bool isEnemyEnded;

};

#endif 