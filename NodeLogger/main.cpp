/*
 * File:   main.cpp
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:34
 */

#include <QApplication>
#include <QDebug>

#include "watcher.h"

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);

	try
	{
		if (QFile::exists(argv[1]))
		{
			qDebug() << "File exist";
//			watcher *myWatcher = new watcher(argv[1]);
		}
		else
			throw std::invalid_argument("Config file does not exist!");
	}
	catch (std::exception& e)
	{
		qDebug() << e.what();
	}

	// create and show your widgets here

	return app.exec();
}
