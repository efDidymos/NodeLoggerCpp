/* 
 * File:   watcher.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:41
 */

#ifndef WATCHER_H
#define	WATCHER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>
#include <QTcpSocket>
#include <QNetworkSession>

struct server {
    QString host;
    quint16 port;
};

class watcher : public QObject
{
    Q_OBJECT

public:
    watcher(const char * pathToFile);
    watcher(const watcher& orig);
    virtual ~watcher();

    void readJson(const char * pathToFile);
    void watch();
    
    void sendToServer(const QString& fileName, const QString& text) const;

public slots:
    void showModified(const QString& fileName);
    void displayError(QAbstractSocket::SocketError socketError) const;

private:
    QString idWatcher;
    
    server targetServer;
    
    QMap<QString, int> map;
    QFileSystemWatcher *watchList;
    
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    
    QNetworkSession *networkSession;
};

#endif	/* WATCHER_H */

