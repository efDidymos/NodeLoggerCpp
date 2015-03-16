/* 
 * File:   Thread.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 17:55
 */

#include "Thread.h"

Thread::Thread(int socketDescriptor, const QString &fortune, QObject *parent) :
QThread(parent),
socketDescriptor(socketDescriptor),
text(fortune)
{
}

Thread::Thread(const Thread& orig)
{
}

Thread::~Thread()
{
}

void Thread::run()
{
	QTcpSocket tcpSocket;

	if (!tcpSocket.setSocketDescriptor(socketDescriptor))
	{
		emit error(tcpSocket.error());
		return;
	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16) 0;
	out << text;
	out.device()->seek(0);
	out << (quint16) (block.size() - sizeof (quint16));

	tcpSocket.write(block);
	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
}
