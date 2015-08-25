#ifndef HASHELEMENT_H
#define HASHELEMENT_H

#include <iostream>

class HashElement
{
public:
    HashElement( std::string, std::string, std::string, int, unsigned int );
    virtual ~HashElement();

    std::string identificador;
    std::string classificacao;
    std::string tipo;

    int deslocamento;
    unsigned int levelLexico;

};

#endif // HASHELEMENT_H
