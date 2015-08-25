#include "hashelementfuncao.h"

HashElementFuncao::HashElementFuncao( std::string _identificador, std::string _classificacao, std::string _tipo, int _deslocamento, unsigned int _levelLexico, unsigned int _qdeParametros, QList<std::string>* _parametros, std::string _retorno )
    : HashElement( _identificador, _classificacao, _tipo, _deslocamento, _levelLexico )
{
    this->qdeParametros = _qdeParametros;
    this->parametros = _parametros;
    this->retorno = _retorno;
}

HashElementFuncao::~HashElementFuncao(){}
