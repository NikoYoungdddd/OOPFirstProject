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

//创建Sock类
class Sock
{
public:
	//构造函数
	Sock();

	//析构函数
	virtual ~Sock();

	//设置成非阻塞模式
	bool setNonBlock()
	{
		SOCK_TYPE fd = _fd;

#ifdef WIN32
		BOOL flg = TRUE;

		//控制Socket的模式
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

	//关闭Sock
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

	//判断Sock是否合法
	bool isValidSocket()
	{
		return _fd != INVALID_SOCKET;
	}

public:

	SOCK_TYPE _fd;
};


//客户端的Sock
class SockClient : public Sock
{
public:
	//构造函数
	SockClient(unsigned short port = 0, const char* ip = NULL);
	//析构函数
	~SockClient() {}
	//连接
	//第一个参数：端口
   //第二个参数：ip地址
	int connect(unsigned short port, const char* ip);
	//接收
	int recv(char* buf, int len);
	//发送
	int send(const char* buf, int len);
};

//服务器端的Sock
class SockServer :public Sock
{
public:
	//构造函数
	SockServer(unsigned short port, const char* ip = NULL)
	{
		//监听
		listen(port, ip);
	}

	//虚构函数
	~SockServer() {}

	//接受连接
	SockClient* accept();
	

protected:
	//监听
	//第一个参数：端口
	//第二个参数：ip地址
	int listen(unsigned short port, const char* ip = NULL);
	
};

#endif
#pragma once
