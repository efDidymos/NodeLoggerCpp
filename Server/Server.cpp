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
	fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
			<< tr("You've got to think about tomorrow.")
			<< tr("You will be surprised by a loud noise.")
			<< tr("You will feel hungry again in another hour.")
			<< tr("You might have mail.")
			<< tr("You cannot kill time without injuring eternity.")
			<< tr("Computers are not intelligent. They only think they are.");
}

Server::Server(const Server& orig)
{
}

Server::~Server()
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	QString fortune = fortunes.at(qrand() % fortunes.size());
	
    Thread *thread = new Thread(socketDescriptor, fortune, this); 
	
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}