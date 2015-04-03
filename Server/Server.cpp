/* 
 * File:   Server.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 11:25
 */

#include "Server.h"
#include "Thread.h"
#include <thread>

Server::Server(QObject *parent) : QTcpServer(parent)
{
#ifdef DEBUG
	qDebug() << "Constructor server";
#endif
}

Server::Server(const Server& orig)
{
}

Server::~Server()
{
#ifdef DEBUG
	qDebug() << "Destructor server";
#endif
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	Thread *thread = new Thread(socketDescriptor, this);
	QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	QObject::connect(thread, SIGNAL(send2MainThread(const QString &, const QString &, const QString &)), this, SLOT(write2db(const QString &, const QString &, const QString &)));
	thread->start();
}

void Server::write2db(const QString & logger, const QString & fileName, const QString & text)
{
	QMutexLocker locker(&dbLock);
		
	qDebug() << "From " << logger << ", in file " << fileName << " received:";
	qDebug() << text;


	qDebug() << "Waiting 5 seconds simulating writing process.";
	
	std::this_thread::sleep_for (std::chrono::seconds(5));
	
	qDebug() << "Writing done!";
}