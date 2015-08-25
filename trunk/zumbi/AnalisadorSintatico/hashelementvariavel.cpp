#include "hashelementvariavel.h"

HashElementVariavel::HashElementVariavel(){}

HashElementVariavel::HashElementVariavel( std::string _identificador, std::string _classificacao, std::string _tipo, int _deslocamento, unsigned int _levelLexico )
    : HashElement( _identificador, _classificacao, _tipo, _deslocamento, _levelLexico )
{
}

HashElementVariavel::~HashElementVariavel(){}
