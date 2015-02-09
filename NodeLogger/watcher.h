/* 
 * File:   watcher.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, februára 8, 11:41
 */

#ifndef WATCHER_H
#define	WATCHER_H

#include <QFile>

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
    std::vector<QString> logFiles;
};

#endif	/* WATCHER_H */

