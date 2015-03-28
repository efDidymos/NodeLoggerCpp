/* 
 * File:   Server.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 11:25
 */

#include "Server.h"
#include "Thread.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
}

Server::Server(const Server& orig)
{
}

Server::~Server()
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	Thread *thread = new Thread(socketDescriptor, this); 
	QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}