#ifndef HASHELEMENTFUNCAO_H
#define HASHELEMENTFUNCAO_H

#include <QList>
#include <QHash>
#include <QString>

#include "hashelement.h"

class HashElementFuncao : public HashElement
{
public:
    HashElementFuncao();
    HashElementFuncao( std::string, std::string, std::string, int, unsigned int, unsigned int, QList<std::string>*, QHash<QString, HashElement*>*, std::string );

    virtual ~HashElementFuncao();

    unsigned int qdeParametros;

    QList<std::string>* parametros;

    QHash<QString, HashElement*>* hash;

    std::string retorno;
};

#endif // HASHELEMENTFUNCAO_H
