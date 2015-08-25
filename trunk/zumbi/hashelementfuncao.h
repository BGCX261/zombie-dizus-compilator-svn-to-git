#ifndef HASHELEMENTFUNCAO_H
#define HASHELEMENTFUNCAO_H

#include <QList>

#include "hashelement.h"

class HashElementFuncao : public HashElement
{
public:
    HashElementFuncao( std::string, std::string, std::string, int, unsigned int, unsigned int, QList<std::string>*, std::string );

    virtual ~HashElementFuncao();

    unsigned int qdeParametros;

    QList<std::string>* parametros;

    std::string retorno;
};

#endif // HASHELEMENTFUNCAO_H
