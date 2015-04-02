/* 
 * File:   Server.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 11:25
 */

#ifndef LISTENER_H
#define	LISTENER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    Server(const Server& orig);
    virtual ~Server();
    
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
};

#endif	/* LISTENER_H */

