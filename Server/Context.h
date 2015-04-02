/* 
 * File:   Context.h
 * Author: tomas
 *
 * Created on Nedeľa, 2015, marca 15, 17:36
 */

#ifndef CONTEXT_H
#define	CONTEXT_H

#include <QObject>
#include "Server.h"

class Context : public QObject
{
    Q_OBJECT
    
public:
/*    Context(QObject *parent = 0);   */
    Context(const char * pathToFile, QObject *parent = 0);
    Context(const Context& orig);
    virtual ~Context();

    void readJson(const char * pathToFile);
    
private:
    Server server;
    qint16 port;
};

#endif	/* CONTEXT_H */

