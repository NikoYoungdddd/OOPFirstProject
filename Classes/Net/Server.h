#ifndef _SERVER_H_
#define _SERVER_H_


#include "Const/Const.h"


class Server
{
public:
	//����ģʽ��ʹ��
	static Server* getInstance();
	
	//�򿪷����� �������0Ϊ���� 1Ϊ������
	BOOL OpenTCPServer(unsigned long block);
	
	//�����Ƿ��пͻ������Ӻ���
	BOOL AcceptClient();
	
	//���ؽ��յ���SOCKET
	SOCKET* GetMySOCKET();
	
	//������Ϣ����
	int SendData(const std::string a, int iSize);
	
	//�������Է���˵���Ϣ���ж���Ϣ����
	int RecvDataAndJudge();
	
	//�ж��Ƿ����
	bool isEnemyEnd();
	
	//��ȡ������Ϣ
	std::string getEnemyData();
	
	//��ȡ��ǰ�յ���������Ϣ
	std::string getMessage();
	
	//�ж�������Ϣ�Ƿ��Ѿ��������������
	bool isMessageDisplayed;
	
	//���浱ǰIP
	std::string myIP;

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