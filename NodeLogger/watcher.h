/* 
 * File:   watcher.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:41
 */

#ifndef WATCHER_H
#define	WATCHER_H

#include <QWidget>
#include <QFile>
#include <QMap>
#include <QFileSystemWatcher>

class watcher : public QWidget
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

private:
    QString target;
    QMap<QString, int> map;
    QFileSystemWatcher *watchList;
};

#endif	/* WATCHER_H */

