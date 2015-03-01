/* 
 * File:   watcher.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:41
 */

#ifndef WATCHER_H
#define	WATCHER_H

#include <QObject>
#include <QFile>
#include <QMap>
#include <QFileSystemWatcher>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkSession>

struct server {
    QString host;
    int port;
};

class watcher : public QObject
{
    Q_OBJECT

public:
    watcher(char * pathToFile);
    watcher(const watcher& orig);
    virtual ~watcher();

    void readJson(char * pathToFile);
    void watch();

public slots:
    void showModified(const QString& fileName);
//    void readFortune();
//    void displayError(QAbstractSocket::SocketError socketError);

private:
    QString idWatcher;
    
    server targetServer;
    
    QMap<QString, int> map;
    QFileSystemWatcher *watchList;
    
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    
    QNetworkSession *networkSession;
};

#endif	/* WATCHER_H */

