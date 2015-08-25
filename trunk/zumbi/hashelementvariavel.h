#ifndef HASHELEMENTVARIAVEL_H
#define HASHELEMENTVARIAVEL_H

#include "hashelement.h"

class HashElementVariavel : public HashElement
{
public:
    HashElementVariavel( std::string, std::string, std::string, int, unsigned int );
    virtual ~HashElementVariavel();

    std::string tipo;
};

#endif // HASHELEMENTVARIAVEL_H
