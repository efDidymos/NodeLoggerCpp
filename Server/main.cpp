/*
 * File:   main.cpp
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:34
 */

#include <QCoreApplication>
#include <csignal>
#include "Context.h"

static void cleanup(int sig)
{
#ifdef DEBUG
	qDebug() << "Caught CTRL+C signal, Bye :)";
#endif
	
	if (sig == SIGINT) qApp->quit();
}

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	signal(SIGINT, cleanup);

	QCoreApplication app(argc, argv);

	//	if (QFile::exists(argv[1]))
	//	{
	Context myServer;

	// create and show your widgets here

	return app.exec();
	//	}
	//	else
	//	{
	//		qCritical() << "Argument error: config file does not exist!";
	//		qDebug() << "Usage:" << argv[0] << "<config file>";
	//		return 0;
	//	}
}
