#include "Sock.h"

//构造函数
Sock::Sock() :_fd(INVALID_SOCKET)
{

#ifdef WIN32

	//初始化Windoes下的Sock
	static bool winInit = false;
	if (!winInit)
	{
		winInit = true;
		WSADATA data;
		WSAStartup(MAKEWORD(2, 2), &data);
	}
#endif
}


//虚构函数
Sock::~Sock()
{
	if (isValidSocket())
	{
		close();
	}
}


SockClient::SockClient(unsigned short port , const char* ip )
{
	if (port == 0 && ip == NULL)
	{
		return;
	}

	//连接
	connect(port, ip);
}


//连接
	//第一个参数：端口
   //第二个参数：ip地址
int SockClient::connect(unsigned short port, const char* ip)
{
	//分配一个Socket
	//第一个参数：AF_INET表示指定地址族(地址描述)
	//第二个参数：SOCK_STREAM表示流式套接字TCP(Socket类型)
	//第三个参数：0(协议)
	_fd = socket(AF_INET, SOCK_STREAM, 0);

	//地址信息结构
	struct sockaddr_in addr;

	//地址家族
	addr.sin_family = AF_INET;

	//端口号
	addr.sin_port = htons(port);

	//主机地址
	addr.sin_addr.s_addr = inet_addr(ip);

	//连接
	int ret = ::connect(_fd, (struct sockaddr*)&addr, sizeof(addr));

	if (ret < 0)
	{
		MyLog("connect error errno=%d", errno);
		return -1;
	}

	return 0;
}

int SockClient::recv(char* buf, int len)
{
	return ::recv(_fd, buf, len, 0);
}

int SockClient::send(const char* buf, int len)
{
	return ::send(_fd, buf, len, 0);
}

SockClient* SockServer::accept()
{
	//接受客户端的发送请求,等待客户端发送connect请求
	SOCK_TYPE fd = ::accept(_fd, NULL, NULL);

	if (fd != INVALID_SOCKET)
	{
		//创建一个SockClient
		SockClient* ret = new SockClient;
		ret->attach(fd);
		return ret;
	}
	return NULL;
}

//监听
	//第一个参数：端口
	//第二个参数：ip地址
int SockServer::listen(unsigned short port, const char* ip )
{
	//分配一个Socket
  //第一个参数：AF_INET表示指定地址族(地址描述)
  //第二个参数：SOCK_STREAM表示流式套接字TCP(Socket类型)
  //第三个参数：0(协议)
	_fd = socket(AF_INET, SOCK_STREAM, 0);

	//地址信息结果
	struct sockaddr_in addr;

	//地址家族
	addr.sin_family = AF_INET;

	//端口号
	addr.sin_port = htons(port);

	if (ip == NULL)
	{
		//设置一个不确定的ip地址
		addr.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		//将ip地址转换为32位二进制网络字节序的IPV4地址
		addr.sin_addr.s_addr = inet_addr(ip);
	}

	//绑定
	int ret = bind(_fd, (struct sockaddr*)&addr, sizeof(addr));

	if (ret < 0)
	{
		MyLog("bind error");
		return -1;
	}

	//设置成非阻塞
	this->setNonBlock();

	//监听
	::listen(_fd, 10);

	return 0;
}