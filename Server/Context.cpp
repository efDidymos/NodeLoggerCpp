/* 
 * File:   Context.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 17:36
 */

#include <QtNetwork>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include "Context.h"
#include <stdexcept>

Context::Context(const char * pathToFile, QObject *parent)
{	
	readJson(pathToFile);
	
	if (!server.listen(QHostAddress::Any, port))
	{
		qDebug() << "Threaded Server";
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
	qDebug() << "\nport: " << port;
	qDebug() << "\n\nRun the Client now.";
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

void Context::readJson(const char * pathToFile)
{
	QString data;
	QJsonParseError jsonEror;
	QFile cFile(QString::fromUtf8(pathToFile));
	
	try
	{
		if (cFile.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			data = cFile.readAll();
			cFile.close();
			
			QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &jsonEror);

			if (jsonEror.error != QJsonParseError::NoError)
				throw std::invalid_argument(jsonEror.errorString().toUtf8().constData());
			
			QJsonObject obj = doc.object();
			
			port = obj["port"].toString().toInt();
			
			qDebug() << "Configuration file leaded succesfully.";
		}
		else
			throw std::invalid_argument("Can not read the config file!");
	}
	catch (std::exception& e)
	{
		qCritical() << "Exception caught: " << e.what();
		qApp->quit();
	}
}

