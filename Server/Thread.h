/* 
 * File:   Thread.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 17:55
 */

#ifndef THREAD_H
#define	THREAD_H

#include <QThread>
#include <QTcpSocket>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(int socketDescriptor, QObject *parent);
    Thread(const Thread& orig);
    virtual ~Thread();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void read();
    void clientDisconnected();

private:
    int socketDescriptor;
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    
    QString currentText;
    QString logger;
};

#endif	/* THREAD_H */

