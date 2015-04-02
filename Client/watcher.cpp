/* 
 * File:   watcher.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, februára 8, 11:41
 */

#include "watcher.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>

watcher::watcher(const char * pathToFile)
{
	readJson(pathToFile);
}

watcher::watcher(const watcher& orig)
{
}

watcher::~watcher()
{
#ifdef DEBUG
	qDebug() << "Destructor watcher";
#endif

	if (watchList) delete watchList;
	watchList = NULL;

	if (tcpSocket) delete tcpSocket;
	tcpSocket = NULL;

	if (networkSession) delete networkSession;
	networkSession = NULL;
}

void watcher::readJson(const char * pathToFile)
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

			idWatcher = obj["id"].toString();
			qDebug() << "This watcher is: " << idWatcher;

			QJsonObject sobj = obj["target"].toObject();
			targetServer.host = sobj["host"].toString();
			targetServer.port = sobj["port"].toString().toInt();

			qDebug() << "Target address is: " << targetServer.host << ":" << targetServer.port;

			QJsonArray files = obj["files"].toArray();

			foreach(QJsonValue file, files)
			if (QFile::exists(file.toString()))
			{
				QFile f(file.toString());

				int pos = 0;

				if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
					qDebug() << "The file " << file.toString() << " can not be read.";
				else
				{
					pos = f.size();

					map.insert(file.toString(), pos);

					f.close();

					qDebug() << "File " << file.toString() << " added to watchlist.";
				}
			}
			else
				qDebug() << "File " << file.toString() << " does not exist!";

			qDebug() << "Configuration file leaded succesfully.";

			watch();
		}
		else
			throw std::invalid_argument("Can not read the config file!");
	}
	catch (std::exception& e)
	{
		qCritical() << "Exception caught: " << e.what();
	}
}

void watcher::watch()
{
	watchList = new QFileSystemWatcher(map.keys());

	QObject::connect(watchList, SIGNAL(fileChanged(const QString &)), this, SLOT(showModified(const QString &)));

	networkSession = NULL;
	tcpSocket = new QTcpSocket(this);

	QObject::connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void watcher::sendToServer(const QString& fileName, const QString& text)
{

	struct Packet
	{
		QString id;
		QString data;
	};

	Packet packet = {idWatcher, text};

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_4);
	out << (quint16) 0;
	out << text << idWatcher << fileName;
	out.device()->seek(0);
	out << (quint16) (block.size() - sizeof (quint16));

#ifdef DEBUG
	qDebug() << "Sending to the server message block of size: ";
	qDebug() << ((quint16) (block.size() - sizeof (quint16)));
#endif

	tcpSocket->connectToHost(targetServer.host, targetServer.port);
	tcpSocket->write(block);
	tcpSocket->disconnectFromHost();
}

void watcher::showModified(const QString& fileName)
{
#ifdef DEBUG
	qDebug() << "The " << fileName << " changed.";
#endif

	QFile f(fileName);

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		qDebug() << "The file " << fileName << " can not be read.";
	else
	{
		f.seek(map.value(fileName));

		QString added;
		while (!f.atEnd())
			added.append(f.readLine());

#ifdef DEBUG
		qDebug() << "Readed data:";
		qDebug() << added;
#endif

		map.insert(fileName, f.pos());

		f.close();

		sendToServer(fileName, added);
	}
}

void watcher::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError)
	{
		case QAbstractSocket::RemoteHostClosedError:
			break;

		case QAbstractSocket::HostNotFoundError:
			qDebug() << "The host was not found. Please check the host name and port settings.";
			break;

		case QAbstractSocket::ConnectionRefusedError:
			qDebug() << "The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct.";
			break;

		default:
			qDebug() << "The following error occurred:" << tcpSocket->errorString();
	}

}