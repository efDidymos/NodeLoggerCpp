/* 
 * File:   Context.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 17:36
 */

#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include "Server.h"

class Initialize : public QObject
{
    Q_OBJECT

public:
    Initialize(const char * pathToFile, QObject *parent = 0);
    Initialize(const Initialize& orig);
    virtual ~Initialize();

    void readJson(const char * pathToFile);

private:
    Server server;
    qint16 port;
};

#endif /* CONTEXT_H */

