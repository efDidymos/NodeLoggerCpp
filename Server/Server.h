/* 
 * File:   Server.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 11:25
 */

#ifndef LISTENER_H
#define	LISTENER_H

#include <QTcpServer>
#include <QMutex>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    Server(const Server& orig);
    virtual ~Server();

/*
signals:
    void send2MainThread(const QString & logger, const QString & fileName, const QString & text);
    
public slots:
    void write2db(const QString & logger, const QString & fileName, const QString & text);
*/
    
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:
    QMutex dbLock;
};

#endif	/* LISTENER_H */

