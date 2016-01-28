/*
 * File:   main.cpp
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:34
 */

#include <QCoreApplication>
#include <QFile>
#include <csignal>
#include "Initialize.h"

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

    if (QFile::exists(argv[1]))
    {
        Initialize myServer(argv[1]);

        // create and show your widgets here
        return app.exec();
    }
    else
    {
        qCritical() << "Argument error: config file '" << argv[1] << "' does not exist!";
        qDebug() << "Usage:" << argv[0] << "<config file>";

        return 0;
    }
}
