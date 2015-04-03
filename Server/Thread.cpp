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
	qDebug() << "Constructor thread";
#endif

	tcpSocket = new QTcpSocket(this);

	if (!tcpSocket->setSocketDescriptor(socketDescriptor))
	{
		emit error(tcpSocket->error());
#ifdef DEBUG
		qDebug() << "Server has errors";
#endif
		return;
	}
	else
	{
#ifdef DEBUG
		qDebug() << "Server is running";
#endif

		blockSize = 0;
		QObject::connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(quit()));
		QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
	}
}

Thread::Thread(const Thread& orig)
{
}

Thread::~Thread()
{
#ifdef DEBUG
	qDebug() << "Destructor thread";
#endif
	delete tcpSocket;
}

void Thread::read()
{
#ifdef DEBUG
	qDebug() << "Received message";
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

	currentText = nextText;

	emit send2MainThread(logger, fileName, currentText);
}