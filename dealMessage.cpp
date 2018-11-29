#include "dealMessage.h"
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")  


GetMessageThread::GetMessageThread()
{
}


GetMessageThread::~GetMessageThread()
{
}

// 启用线程
void GetMessageThread::run()
{
	//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return ;
	}

	//创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, 0);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return ;
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return ;
	}

	//循环接收数据  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while (true)
	{
		printf("等待连接...\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		//接收数据  
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}

		//发送数据  
		const char * sendData = "你好，TCP客户端！\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}

	closesocket(slisten);
	WSACleanup();
}


SendMessageThread::SendMessageThread()
{
}


SendMessageThread::~SendMessageThread()
{
}

// 启用线程
void SendMessageThread::run()
{

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return ;
	}
	while (true) 
	{
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, 0);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket!");
			return ;
		}
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888);
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		if (::connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //连接失败 
			printf("connect error !");
			closesocket(sclient);
			return ;
		}
		char * sendData = "你好，TCP服务端，我是客户端\n";
		send(sclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 

		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret>0)
		{
			recData[ret] = 0x00;
			printf(recData);
		}
		closesocket(sclient);
	}
	return;
}
