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
    Thread(int socketDescriptor, const QString &fortune, QObject *parent);
    Thread(const Thread& orig);
    virtual ~Thread();

    void run() Q_DECL_OVERRIDE;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};

#endif	/* THREAD_H */

