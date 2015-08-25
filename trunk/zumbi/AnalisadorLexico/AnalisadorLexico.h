#ifndef ANALISADORLEXICO_H_
#define ANALISADORLEXICO_H_

#include <iostream>
#include <list>
#include <map>
#include <string>

#include "./AutomatoFD.h"
#include "./StructToken.h"

class AnalisadorLexico
{
	public:
		AnalisadorLexico( const std::string, const std::string );

		AnalisadorLexico( const std::string );

		std::map<int, StructToken>
		getMapAnalisadorLexico( );

	protected:
		virtual
		~AnalisadorLexico( );

	private:
		AutomatoFD*
		automato;

		std::list<std::string>
		codigoFonte;

		std::map<int, StructToken>
		saidaAnalisadorLexico;

		void
		carregaCodigo( const std::string );

		void
		salvaLog( const std::string );

		void
		ImprimeLog( );
};

#endif /*ANALISADORLEXICO_H_*/
