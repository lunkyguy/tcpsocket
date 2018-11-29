#pragma once
#include <qthread.h>


//接收报文
class GetMessageThread :
	public QThread
{
public:
	GetMessageThread();
	~GetMessageThread();
	// 启用线程
	void run();
};

//发送报文
class SendMessageThread :
	public QThread
{
public:
	SendMessageThread();
	~SendMessageThread();
	// 启用线程
	void run();
};

