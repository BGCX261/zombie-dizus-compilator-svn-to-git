#include "hashelementparametroformal.h"

HashElementParametroFormal::HashElementParametroFormal(){}

HashElementParametroFormal::HashElementParametroFormal( std::string _identificador, std::string _classificacao, std::string _tipo, int _deslocamento, unsigned int _levelLexico, std::string _passagem )
    : HashElement( _identificador, _classificacao, _tipo, _deslocamento, _levelLexico )
{
    this->passagem = "";
}
