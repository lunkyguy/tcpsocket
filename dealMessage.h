#pragma once
#include <qthread.h>


//���ձ���
class GetMessageThread :
	public QThread
{
public:
	GetMessageThread();
	~GetMessageThread();
	// �����߳�
	void run();
};

//���ͱ���
class SendMessageThread :
	public QThread
{
public:
	SendMessageThread();
	~SendMessageThread();
	// �����߳�
	void run();
};

