/* 
 * File:   watcher.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:41
 */

#ifndef WATCHER_H
#define	WATCHER_H

#include <QFile>
#include <QVector>

class watcher
{
public:
    watcher(char * pathToFile);
    watcher(const watcher& orig);
    virtual ~watcher();
    
    void readJson();
    
private:
    QFile *cFile;
    QString target;
    QVector<QString> logFiles;
};

#endif	/* WATCHER_H */

