/* 
 * File:   Context.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 17:36
 */

#include <QtNetwork>
#include "Context.h"

Context::Context(QObject *parent)
{	
	if (!server.listen())
	{
		qDebug() << "Threaded Fortune Server";
		qDebug() << "Unable to start the server: " << server.errorString();
		return;
	}

	QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

	// use the first non-localhost IPv4 address
	for (int i = 0; i < ipAddressesList.size(); ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
				ipAddressesList.at(i).toIPv4Address())
		{
			ipAddress = ipAddressesList.at(i).toString();
			break;
		}
	}

	// if we did not find one, use IPv4 localhost
	if (ipAddress.isEmpty())
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

	qDebug() << "The server is running on\n\nIP: " << ipAddress;
	qDebug() << "\nport: " << server.serverPort();
	qDebug() << "\n\nRun the Fortune Client example now.";
}

Context::Context(const Context& orig)
{
}

Context::~Context()
{
#ifdef DEBUG
	qDebug() << "Destructor context";
#endif
}

