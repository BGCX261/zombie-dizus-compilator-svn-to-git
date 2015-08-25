#ifndef HASHELEMENTVARIAVEL_H
#define HASHELEMENTVARIAVEL_H

#include "hashelement.h"

class HashElementVariavel : public HashElement
{
public:
    HashElementVariavel();
    HashElementVariavel( std::string, std::string, std::string, int, unsigned int );
    virtual ~HashElementVariavel();
};

#endif // HASHELEMENTVARIAVEL_H
