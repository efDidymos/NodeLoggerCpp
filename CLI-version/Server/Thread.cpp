/* 
 * File:   Thread.cpp
 * Author: tomas
 * 
 * Created on Nedeľa, 2015, marca 15, 17:55
 */

#include "Thread.h"
#include <QObject>
#include <QTimer>
#include <thread>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <ctime>

#include <QDebug>
#include <QDataStream>

Thread::Thread(int socketDescriptor, QMutex *lock, QObject *parent) :
socketDescriptor(socketDescriptor),
QThread(parent),
lock(lock)
{
#ifdef DEBUG
    qDebug() << "Constructor thread";
#endif

    tcpSocket = new QTcpSocket(this);

    if (!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket->error());
#ifdef DEBUG
        qDebug() << "Server has errors";
#endif
        return;
    }
    else
    {
#ifdef DEBUG
        qDebug() << "Server is running";
#endif

        blockSize = 0;
        QObject::connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(quit()));
        QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    }
}

Thread::Thread(const Thread& orig)
{
}

Thread::~Thread()
{
#ifdef DEBUG
    qDebug() << "Destructor thread";
#endif
    if (tcpSocket) delete tcpSocket;
    tcpSocket = NULL;
    if (lock) delete lock;
    lock = NULL;
}

void Thread::read()
{
#ifdef DEBUG
    qDebug() << "Received message";
#endif

    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (blockSize == 0)
    {
        if (tcpSocket->bytesAvailable() < (int) sizeof (quint16))
            return;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    QString nextText, fileName;
    in >> nextText >> logger >> fileName;

    currentText = nextText;

    QMutexLocker locker(lock);

    qDebug() << "From " << logger << ", in file " << fileName << " received:";
    qDebug() << nextText;


    qDebug() << "Waiting 5 seconds simulating writing process.";

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "myDB");
        db.setHostName("localhost");
        db.setDatabaseName("nodelogger");
        db.setUserName("kaskaderi");
        db.setPassword("slovensko");

        if (!db.open()) qDebug() << "Error connecting to database";
        else
        {
            QSqlQuery query(db);
            query.prepare("INSERT INTO data (fromNode, whenCame, inFileOfNode, text) "
                          "VALUES (:fromNode, :whenCame, :inFileOfNode, :text)");

            std::time_t epoch = std::time(NULL);
            char actualTime[100];
            std::strftime(actualTime, sizeof (actualTime), "%Y-%m-%d %H:%M:%S", std::localtime(&epoch));

            query.bindValue(":fromNode", logger);
            query.bindValue(":whenCame", actualTime);
            query.bindValue(":inFileOfNode", fileName);
            query.bindValue(":text", nextText);
            query.exec();

            db.close();
        }
    }

    QSqlDatabase::removeDatabase("myDB");

    //	std::this_thread::sleep_for(std::chrono::seconds(5));

    //	emit send2MainThread(logger, fileName, currentText);

    qDebug() << "Writing done!";
}