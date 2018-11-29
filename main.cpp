#include <QtCore/QCoreApplication>
#include "dealMessage.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	GetMessageThread getMessage;
	SendMessageThread sendMessage;
	getMessage.start();
	sendMessage.start();
	return a.exec();
}
