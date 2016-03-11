/* 
 * File:   Thread.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 17:55
 */

#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(int socketDescriptor, QMutex *lock, QObject *parent);
    Thread(const Thread& orig) = delete;
    virtual ~Thread();

signals:
    //    void send2MainThread(const QString & logger, const QString & fileName, const QString & text);
    void error(QTcpSocket::SocketError socketError);

public slots:
    void read();

private:
    int socketDescriptor;
    QTcpSocket *tcpSocket;
    QMutex *lock;
    quint16 blockSize;

    QString currentText;
    QString logger;
};

#endif /* THREAD_H */

