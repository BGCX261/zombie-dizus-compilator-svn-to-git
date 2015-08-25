#include "hashelement.h"

HashElement::HashElement( std::string _identificador, std::string _classificacao, std::string _tipo, int _deslocamento, unsigned int _levelLexico )
{
    this->identificador = _identificador;
    this->classificacao = _classificacao;
    this->tipo = _tipo;
    this->deslocamento = _deslocamento;
    this->levelLexico = _levelLexico;
}

HashElement::~HashElement(){}
