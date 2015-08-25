#include <fstream>
#include <iostream>
#include <map>
#include <regex.h>
#include <sstream>
#include <string>
#include <cstdlib>

#include "AnalisadorLexico.h"
#include "ErrosExecucao.h"
#include "StructToken.h"


AnalisadorLexico::AnalisadorLexico( const std::string caminhoCodigo, const std::string caminhoLog )
{
	try
	{
		this->carregaCodigo( caminhoCodigo );

		this->automato = new AutomatoFD( this->codigoFonte );
		this->saidaAnalisadorLexico = this->automato->getSaidaAutomato( );

		this->salvaLog( caminhoLog );
	}
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( ) << std::endl;
		exit (1);
	}
}
AnalisadorLexico::AnalisadorLexico( const std::string caminhoCodigo )
{
	try
	{
		this->carregaCodigo( caminhoCodigo );

		this->automato = new AutomatoFD( this->codigoFonte );
		this->saidaAnalisadorLexico = this->automato->getSaidaAutomato( );

		this->ImprimeLog( );
	}
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( ) << std::endl;
		exit (1);
	}
}

AnalisadorLexico::~AnalisadorLexico( )
{
	delete this->automato;
}

std::map<int, StructToken>
AnalisadorLexico::getMapAnalisadorLexico( )
{
	return this->saidaAnalisadorLexico;
}


void
AnalisadorLexico::carregaCodigo( const std::string caminho )
{
	std::ifstream
	arquivoCodigo;

	std::string
	bufferLinhaCodigo;

	size_t
	found;

//	int
//	(*pf) (int) = tolower;

	char
	bufferCaractere[1024];

	regex_t
	expressaoRegular;

	if ( regcomp(&expressaoRegular, ".pas$", REG_EXTENDED|REG_ICASE|REG_NOSUB) )	throw ( new ErrosExecucao("A expressao regular nao pode ser alocada") );

	if ( regexec(&expressaoRegular, caminho.c_str(), 0, (regmatch_t *)NULL, 0) ) throw ( new ErrosExecucao("O formato do arquivo nao e valido...") );

	regfree( &expressaoRegular );

	arquivoCodigo.open( caminho.c_str(), std::ifstream::in );
	if ( arquivoCodigo.bad() ) throw ( new ErrosExecucao("O arquivo de codigo nao pode ser aberto!! Sucesso;;") );

	arquivoCodigo.seekg ( 0, std::ios::beg );

	bufferLinhaCodigo.clear( );

	while ( arquivoCodigo.good() )
	{
		arquivoCodigo.getline( bufferCaractere, 1024 );
		bufferLinhaCodigo = bufferCaractere;
//		std::cout << bufferLinhaCodigo << " - " << bufferLinhaCodigo.size() << std::endl;

		found = bufferLinhaCodigo.find_first_of( '\t' );
		while( found != std::string::npos )
		{
			bufferLinhaCodigo.erase( found, 1 );
			found = bufferLinhaCodigo.find_first_of( '\t' );
		}

//		std::transform(bufferLinhaCodigo.begin( ), bufferLinhaCodigo.end( ), bufferLinhaCodigo.begin( ), pf);

		if ( bufferLinhaCodigo.size() != 0 )
		{
			this->codigoFonte.push_back( bufferLinhaCodigo + ' ' );
		}
		bufferLinhaCodigo.clear();

	}
	arquivoCodigo.close( );
}

void
AnalisadorLexico::salvaLog( const std::string caminhoLog )
{
	std::map<int, StructToken>::iterator
	iteradorLog;

	std::stringstream
	buffer[ this->saidaAnalisadorLexico.size() ];

	std::string
	bufferString;

	unsigned int
	contadorBuffer = 0;

	std::ofstream
	arquivoLog;

	arquivoLog.open( caminhoLog.c_str(), std::ifstream::out );
	if ( arquivoLog.bad() ) throw ( new ErrosExecucao("O arquivo de log nao pode ser criado!! Sucesso;;") );

	for( iteradorLog = this->saidaAnalisadorLexico.begin(); iteradorLog != this->saidaAnalisadorLexico.end(); ++iteradorLog )
	{
		buffer[ contadorBuffer ] << '[' << iteradorLog->first << "] [" << iteradorLog->second.linha << "] [" << iteradorLog->second.token << "] [" << iteradorLog->second.classificacao << ']' << std::endl;

		bufferString = buffer[contadorBuffer].str();

		arquivoLog.write( bufferString.c_str(), bufferString.size() );

		++contadorBuffer;
	}
	arquivoLog.close( );
}

void
AnalisadorLexico::ImprimeLog( )
{
	std::map<int, StructToken>::iterator
	iteradorLog;

	std::stringstream
	buffer[ this->saidaAnalisadorLexico.size() ];

	unsigned int
	contadorBuffer = 0;

	for( iteradorLog = this->saidaAnalisadorLexico.begin(); iteradorLog != this->saidaAnalisadorLexico.end(); ++iteradorLog )
	{
		buffer[ contadorBuffer ] << '[' << iteradorLog->first << "] [" << iteradorLog->second.linha << "] [" << iteradorLog->second.token << "] [" << iteradorLog->second.classificacao << ']';
		std::cout << buffer[ contadorBuffer ].str( ) << std::endl;

		++contadorBuffer;
	}
}
