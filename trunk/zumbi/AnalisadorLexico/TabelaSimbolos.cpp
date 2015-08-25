#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ErrosExecucao.h"
#include "StructSimbolo.h"
#include "TabelaSimbolos.h"

TabelaSimbolos*
TabelaSimbolos::instanciaTabelaSimbolos = 0;

TabelaSimbolos*
TabelaSimbolos::getInstancia( )
{
	if ( TabelaSimbolos::instanciaTabelaSimbolos == NULL)
	{
		TabelaSimbolos::instanciaTabelaSimbolos = new TabelaSimbolos( );
    }

	return TabelaSimbolos::instanciaTabelaSimbolos;
}

const std::string
TabelaSimbolos::procuraSimbolo( std::string tokenProcurado )
{
	std::map<std::string, std::string>::iterator
	iteradorBusca;

	iteradorBusca = TabelaSimbolos::instanciaTabelaSimbolos->simbolos.find( tokenProcurado );

	if ( iteradorBusca != TabelaSimbolos::instanciaTabelaSimbolos->simbolos.end() )
	{
		return iteradorBusca->second;
	}
	else
	{
		return "IDENTIFICADOR";
	}
}

TabelaSimbolos::TabelaSimbolos( )
{
	this->criaTabelaTokens( );
}

TabelaSimbolos::~TabelaSimbolos( )
{

}

const std::vector<std::string>
TabelaSimbolos::carregaArquivoConfiguracao( )
{
	std::ifstream
        arquivoConfiguracao ( "../../testes/pascal.conf", std::ifstream::in );

	std::string
	_buffer;

	std::vector<std::string>
	primeiroParser;

        if ( !arquivoConfiguracao.good() ) throw ( new ErrosExecucao("O arquivo de Configuracoes nao pode ser aberto! Sucesso;;") );
        arquivoConfiguracao.seekg( 0, std::ios::beg );

        while ( !arquivoConfiguracao.eof() )
	{
		arquivoConfiguracao >> _buffer;
		primeiroParser.push_back( _buffer );
	}

        arquivoConfiguracao.close( );

        return primeiroParser;
}

void
TabelaSimbolos::criaTabelaTokens( )
{
	size_t
	posicao;

	std::vector<std::string>::iterator
	iteradorPrimeiroParser;

	const std::string
	caracterProcurado = "@";

	std::string
	tipoTemporario;

	std::vector<std::string>
	PrimeiroParser;
	PrimeiroParser = this->carregaArquivoConfiguracao( );

	for (iteradorPrimeiroParser = PrimeiroParser.begin(); iteradorPrimeiroParser != PrimeiroParser.end(); ++iteradorPrimeiroParser)
	{
		posicao = iteradorPrimeiroParser->find( caracterProcurado );

		if ( posicao != std::string::npos )
		{
			tipoTemporario = iteradorPrimeiroParser->substr( posicao+1, iteradorPrimeiroParser->size() );
			++iteradorPrimeiroParser;
		}

		this->simbolos.insert ( std::pair<const std::string, const std::string> (*iteradorPrimeiroParser, tipoTemporario) );
	}
}
