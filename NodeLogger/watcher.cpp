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
#include <QDebug>

watcher::watcher(char * pathToFile)
{
	cFile = new QFile(QString::fromUtf8(pathToFile));
	readJson();
	watch();
}

watcher::watcher(const watcher& orig)
{
}

watcher::~watcher()
{
	delete cFile;
	delete w;
}

/*
 * Preparation function for reading file
//	QFileInfo info1(str);
//	qDebug() << info1.size();

	pathToFile = QString::fromUtf8(pathToFile);
	
	cFile = new QFile(QString::fromUtf8(pathToFile));

	if (!cFile->open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	while (!cFile->atEnd())
	{
		QByteArray line = cFile->readLine();
		cFile->r
//		process_line(line);
		qDebug() << line;
	}
 */

void watcher::readJson()
{
	QString data;
	QJsonParseError jsonEror;

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

			target = obj["target"].toString();
			qDebug() << "Target address is: " << target;
			
			QJsonArray files = obj["files"].toArray();

			foreach(QJsonValue file, files)
				if (QFile::exists(file.toString()))
				{
					logFiles.push_back(file.toString());
					qDebug() << "File " << file.toString() << " added to watchlist.";
				}
				else
					qDebug() << "File " << file.toString() << " does not exist!";
				
			qDebug() << "Configuration file leaded succesfully.";
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
	w = new QFileSystemWatcher(logFiles);

	QObject::connect(w, SIGNAL(fileChanged(const QString &)), this, SLOT(showModified(const QString &)));
}

void watcher::showModified(const QString& fileName)
{
	qDebug() << "The " << fileName << " changed.";
}