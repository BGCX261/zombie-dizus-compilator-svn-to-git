#ifndef HASHELEMENT_H
#define HASHELEMENT_H

#include <iostream>
#include <QList>
#include <QHash>
#include <QString>

class HashElement
{
public:
    HashElement();
    HashElement( std::string, std::string, std::string, int, unsigned int );
    virtual ~HashElement();

    std::string identificador;
    std::string classificacao;
    std::string tipo;

    int deslocamento;
    unsigned int levelLexico;

    unsigned int qdeParametros;

    QList<std::string>* parametros;

    QHash<QString, HashElement*>* hash;

    std::string retorno;

    std::string passagem;

};

#endif // HASHELEMENT_H
