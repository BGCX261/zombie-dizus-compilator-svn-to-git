#include <map>

#include "../AnalisadorLexico/StructToken.h"
#include "../AnalisadorLexico/AnalisadorLexico.h"
#include "../AnalisadorLexico/ErrosExecucao.h"
#include "../AnalisadorLexico/LogErros.h"

#include "AnalisadorSintatico.h"


int
main(int argc, char* argv[])
{
        AnalisadorLexico*
        lexico;

        AnalisadorSintatico*
        sintatico;

        std::string source;

        source = argv[1];

        lexico = new AnalisadorLexico( source );
        sintatico = new AnalisadorSintatico( lexico->getMapAnalisadorLexico( ) );
}


