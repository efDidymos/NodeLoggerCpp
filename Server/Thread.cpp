/* 
 * File:   Thread.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 17:55
 */

#include "Thread.h"
#include <QObject>
#include <QTimer>

Thread::Thread(int socketDescriptor, QObject *parent) :
socketDescriptor(socketDescriptor),
QThread(parent)
{
#ifdef DEBUG
	qDebug() << "Konstruktor thread";
#endif

	tcpSocket = new QTcpSocket(this);

	if (!tcpSocket->setSocketDescriptor(socketDescriptor))
	{
		emit error(tcpSocket->error());
#ifdef DEBUG
		qDebug() << "Server ma problemy";
#endif
		return;
	}
	else
	{
#ifdef DEBUG
		qDebug() << "Server bezi";
#endif

		blockSize = 0;
		QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
	}
}

Thread::Thread(const Thread& orig)
{
}

Thread::~Thread()
{
#ifdef DEBUG
	qDebug() << "Destruktor thread";
#endif
}

void Thread::read()
{
#ifdef DEBUG
	qDebug() << "Prijala sa sprava";
#endif

	QDataStream in(tcpSocket);
	in.setVersion(QDataStream::Qt_5_0);

	if (blockSize == 0)
	{
		if (tcpSocket->bytesAvailable() < (int) sizeof (quint16))
			return;

		in >> blockSize;
	}

	if (tcpSocket->bytesAvailable() < blockSize)
		return;

	QString nextText, fileName;
	in >> nextText >> logger >> fileName;

	if (nextText == currentText)
	{
		//		QTimer::singleShot(0, this, SLOT(conectServer()));
#ifdef DEBUG
		qDebug() << "QTimer::singleShot(0, this, SLOT(conectServer()))";
#endif
		return;
	}

	currentText = nextText;

	qDebug() << "Od " << logger << ", v subore " << fileName << " prijaty text:";
	qDebug() << currentText;
}