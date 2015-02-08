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
    watcher();
    watcher(const watcher& orig);
    virtual ~watcher();

private:
    QFile *cFile;
};

#endif	/* WATCHER_H */

