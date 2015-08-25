#ifndef ERROSEXECUCAO_H_
#define ERROSEXECUCAO_H_

#include <iostream>
#include <string>

class ErrosExecucao
{
	public:
		ErrosExecucao( std::string );

		const std::string
		getErro( );

	protected:
		virtual
		~ErrosExecucao( );

	private:
		std::string
		erro;
};

#endif /*ERROSEXECUCAO_H_*/
