#include "Sock.h"

//���캯��
Sock::Sock() :_fd(INVALID_SOCKET)
{

#ifdef WIN32

	//��ʼ��Windoes�µ�Sock
	static bool winInit = false;
	if (!winInit)
	{
		winInit = true;
		WSADATA data;
		WSAStartup(MAKEWORD(2, 2), &data);
	}
#endif
}


//�鹹����
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

	//����
	connect(port, ip);
}


//����
	//��һ���������˿�
   //�ڶ���������ip��ַ
int SockClient::connect(unsigned short port, const char* ip)
{
	//����һ��Socket
	//��һ��������AF_INET��ʾָ����ַ��(��ַ����)
	//�ڶ���������SOCK_STREAM��ʾ��ʽ�׽���TCP(Socket����)
	//������������0(Э��)
	_fd = socket(AF_INET, SOCK_STREAM, 0);

	//��ַ��Ϣ�ṹ
	struct sockaddr_in addr;

	//��ַ����
	addr.sin_family = AF_INET;

	//�˿ں�
	addr.sin_port = htons(port);

	//������ַ
	addr.sin_addr.s_addr = inet_addr(ip);

	//����
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
	//���ܿͻ��˵ķ�������,�ȴ��ͻ��˷���connect����
	SOCK_TYPE fd = ::accept(_fd, NULL, NULL);

	if (fd != INVALID_SOCKET)
	{
		//����һ��SockClient
		SockClient* ret = new SockClient;
		ret->attach(fd);
		return ret;
	}
	return NULL;
}

//����
	//��һ���������˿�
	//�ڶ���������ip��ַ
int SockServer::listen(unsigned short port, const char* ip )
{
	//����һ��Socket
  //��һ��������AF_INET��ʾָ����ַ��(��ַ����)
  //�ڶ���������SOCK_STREAM��ʾ��ʽ�׽���TCP(Socket����)
  //������������0(Э��)
	_fd = socket(AF_INET, SOCK_STREAM, 0);

	//��ַ��Ϣ���
	struct sockaddr_in addr;

	//��ַ����
	addr.sin_family = AF_INET;

	//�˿ں�
	addr.sin_port = htons(port);

	if (ip == NULL)
	{
		//����һ����ȷ����ip��ַ
		addr.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		//��ip��ַת��Ϊ32λ�����������ֽ����IPV4��ַ
		addr.sin_addr.s_addr = inet_addr(ip);
	}

	//��
	int ret = bind(_fd, (struct sockaddr*)&addr, sizeof(addr));

	if (ret < 0)
	{
		MyLog("bind error");
		return -1;
	}

	//���óɷ�����
	this->setNonBlock();

	//����
	::listen(_fd, 10);

	return 0;
}