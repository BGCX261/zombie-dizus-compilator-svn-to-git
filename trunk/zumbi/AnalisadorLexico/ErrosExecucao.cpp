#include <iostream>
#include <string>

#include "ErrosExecucao.h"

ErrosExecucao::ErrosExecucao( std::string _erro )
{
	this->erro = _erro;
}

const std::string
ErrosExecucao::getErro( )
{
	return this->erro;
}

ErrosExecucao::~ErrosExecucao( )
{
}
