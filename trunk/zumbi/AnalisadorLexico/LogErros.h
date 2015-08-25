#ifndef LOGERROS_H_
#define LOGERROS_H_

#include <iostream>
#include <string>
#include <queue>

class LogErros
{
	public:
		static LogErros&
		getInstancia( );

		void
		insereErro( const unsigned int, const std::string );

		void
		getLog( );

		bool
		getQuantidadeErros( );

	protected:
		LogErros( );

		virtual
		~LogErros( );

	private:
		static std::queue<std::string>
		erros;
};

#endif /*LOGERROS_H_*/
