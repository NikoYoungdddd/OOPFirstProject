#ifndef __Sock_H__
#define __Sock_H__

#ifdef WIN32
#include <WinSock2.h>
#define SOCK_TYPE SOCKET
#else
#define SOCK_TYPE int
#define INVALID_SOCKET -1
#endif

#define MyLog(...) 

//����Sock��
class Sock
{
public:
	//���캯��
	Sock();

	//��������
	virtual ~Sock();

	//���óɷ�����ģʽ
	bool setNonBlock()
	{
		SOCK_TYPE fd = _fd;

#ifdef WIN32
		BOOL flg = TRUE;

		//����Socket��ģʽ
		if (ioctlsocket(fd, FIONBIO, (unsigned long*)&flg) != 0)
		{
			return false;
		}

		return true;

#else
		int flags = fcntl(fd, F_GETFL, 0);
		flags |= O_NONBLOCK;
		return fcntl(fd, F_SETFL, flags) != -1;
#endif
	}

	//�ر�Sock
	void close()
	{
#ifdef WIN32
		closesocket(_fd);
#else
		::close(_fd);
#endif
	}

	void attach(SOCK_TYPE fd)
	{
		_fd = fd;
	}

	//�ж�Sock�Ƿ�Ϸ�
	bool isValidSocket()
	{
		return _fd != INVALID_SOCKET;
	}

public:

	SOCK_TYPE _fd;
};


//�ͻ��˵�Sock
class SockClient : public Sock
{
public:
	//���캯��
	SockClient(unsigned short port = 0, const char* ip = NULL);
	//��������
	~SockClient() {}
	//����
	//��һ���������˿�
   //�ڶ���������ip��ַ
	int connect(unsigned short port, const char* ip);
	//����
	int recv(char* buf, int len);
	//����
	int send(const char* buf, int len);
};

//�������˵�Sock
class SockServer :public Sock
{
public:
	//���캯��
	SockServer(unsigned short port, const char* ip = NULL)
	{
		//����
		listen(port, ip);
	}

	//�鹹����
	~SockServer() {}

	//��������
	SockClient* accept();
	

protected:
	//����
	//��һ���������˿�
	//�ڶ���������ip��ַ
	int listen(unsigned short port, const char* ip = NULL);
	
};

#endif
#pragma once
