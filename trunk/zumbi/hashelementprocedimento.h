#ifndef HASHELEMENTPROCEDIMENTO_H
#define HASHELEMENTPROCEDIMENTO_H

#include "hashelement.h"

#include<QList>

class HashElementProcedimento : public HashElement
{
public:
    HashElementProcedimento( std::string, std::string, std::string, int, unsigned int, unsigned int, QList<std::string>* );

    virtual ~HashElementProcedimento();

    unsigned int qdeParametros;

    QList<std::string>* parametros;
};

#endif // HASHELEMENTPROCEDIMENTO_H
