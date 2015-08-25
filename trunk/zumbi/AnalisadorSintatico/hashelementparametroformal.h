#ifndef HASHELEMENTPARAMETROFORMAL_H
#define HASHELEMENTPARAMETROFORMAL_H

#include "hashelement.h"

class HashElementParametroFormal : public HashElement
{
public:
    HashElementParametroFormal();
    HashElementParametroFormal( std::string, std::string, std::string, int, unsigned int, std::string );

    std::string passagem;
};

#endif // HASHELEMENTPARAMETROFORMAL_H
