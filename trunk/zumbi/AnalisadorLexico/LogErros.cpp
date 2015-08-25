#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "LogErros.h"

std::queue<std::string>
LogErros::erros;

LogErros&
LogErros::getInstancia( )
{
	static LogErros
	log;

	return log;
}

void
LogErros::insereErro( const unsigned int numeroLinha, const std::string erro )
{
	std::stringstream
	linhaErro;

	linhaErro << "[Linha " << numeroLinha << "] - " << erro;

	LogErros::erros.push( linhaErro.str() );
}

void
LogErros::getLog( )
{
	if ( !LogErros::erros.empty() )
	{
		while ( !LogErros::erros.empty() )
		{
			std::cout << LogErros::erros.front() << std::endl;
			LogErros::erros.pop( );
		}
	}
	else
	{
		std::cout << "Nao foram encontrados erros..." << std::endl << std::endl;
	}
}

bool
LogErros::getQuantidadeErros( )
{
	return LogErros::erros.empty( );
}



LogErros::LogErros( )
{
}

LogErros::~LogErros( )
{
}



