#ifndef HASHELEMENTPROCEDIMENTO_H
#define HASHELEMENTPROCEDIMENTO_H

#include "hashelement.h"

#include <QList>
#include <QHash>
#include <QString>

class HashElementProcedimento : public HashElement
{
public:
    HashElementProcedimento();
    HashElementProcedimento( std::string, std::string, std::string, int, unsigned int, unsigned int, QList<std::string>*, QHash<QString, HashElement*>* );

    virtual ~HashElementProcedimento();

    unsigned int qdeParametros;

    QList<std::string>* parametros;

    QHash<QString, HashElement*>* hash;
};

#endif // HASHELEMENTPROCEDIMENTO_H
