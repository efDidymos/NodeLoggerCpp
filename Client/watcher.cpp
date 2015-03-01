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
#include <QTimer>
#include <QDebug>

watcher::watcher(char * pathToFile) : networkSession(0)
{
	readJson(pathToFile);
}

watcher::watcher(const watcher& orig)
{
}

watcher::~watcher()
{
	delete watchList;
}

void watcher::readJson(char * pathToFile)
{
	QString data;
	QJsonParseError jsonEror;
	QFile *cFile = new QFile(QString::fromUtf8(pathToFile));

	try
	{
		if (cFile->open(QIODevice::ReadOnly | QIODevice::Text))
		{
			data = cFile->readAll();
			cFile->close();

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

	tcpSocket = new QTcpSocket(this);
	
	conectServer();

	QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
	QObject::connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void watcher::conectServer()
{
	blockSize = 0;
	tcpSocket->abort();

	tcpSocket->connectToHost(targetServer.host, targetServer.port);
}

void watcher::showModified(const QString& fileName)
{
	qDebug() << "The " << fileName << " changed.";

	QFile f(fileName);

	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		qDebug() << "The file " << fileName << " can not be read.";
	else
	{
		f.seek(map.value(fileName));

		while (!f.atEnd())
			qDebug() << f.readLine();

		map.insert(fileName, f.pos());

		f.close();
	}
}

void watcher::readFortune()
{
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
	
	QString nextFortune;
	in >> nextFortune;

	if (nextFortune == currentFortune)
	{
		QTimer::singleShot(0, this, SLOT(conectServer()));
		return;
	}

	currentFortune = nextFortune;
	
	qDebug() << "precitane: " << currentFortune;
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
			qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
			break;

		default:
			qDebug() << "The following error occurred:" << tcpSocket->errorString();
	}

}