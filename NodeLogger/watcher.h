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
#include <QStringList>
#include <QFileSystemWatcher>

class watcher : public QWidget
{
    Q_OBJECT

public:
    watcher(char * pathToFile);
    watcher(const watcher& orig);
    virtual ~watcher();

    void readJson();
    void watch();

public slots:
    void showModified(const QString& fileName);

private:
    QFile *cFile;
    QString target;
    QStringList logFiles;
    QFileSystemWatcher *w;
};

#endif	/* WATCHER_H */

