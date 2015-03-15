/* 
 * File:   listener.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 11:25
 */

#ifndef LISTENER_H
#define	LISTENER_H

#include <QObject>
#include <QTcpServer>
#include <QNetworkSession>

class server : public QObject
{
    Q_OBJECT

public:
    server();
    server(const server& orig);
    virtual ~server();

private slots:
    void sessionOpened();
    void sendFortune();

private:
    QTcpServer *tcpServer;
    QStringList fortunes;
    QNetworkSession *networkSession;
};

#endif	/* LISTENER_H */

