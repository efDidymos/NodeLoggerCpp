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

	if (QFile::exists(argv[1]))
	{
		watcher * myWatcher = new watcher(argv[1]);

		// create and show your widgets here

		return app.exec();
	}
	else
	{
		qCritical() << "Argument error: config file does not exist!";
		qDebug() << "Usage:" << argv[0] << "<config file>";
		return 0;
	}
}
