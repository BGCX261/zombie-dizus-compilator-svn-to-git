#include "producoes.h"

#include "errosintatico.h"
#include "hashnode.h"

#include <QDebug>

unsigned int
qHash( std::string _chave )
{
    int hash = 0;
    int ascii = 0;
    const unsigned int alfa = 101;
    const unsigned int max_hash_size = 200;

    for (int contador = 0; contador < _chave.size() ;contador++)
    {
         ascii = _chave[contador];
         hash = hash * alfa + ascii;
    }

    hash = hash % max_hash_size;
    return hash;
}

Sintatico::Producoes::Producoes()
{

}

Sintatico::Producoes::~Producoes()
{

}

void
Sintatico::Producoes::prodPrograma()
{
    if ( this->getCurrentToken().value == "PA_PROGRAM" )
    {
        this->nextToken();

        this->prodIdentificador();

	this->checkTerminal("OP_ABR_PAR");
        this->checkTerminal("OP_FCH_PAR");

        this->checkTerminal("OP_PTVG");

        this->prodBloco();

        this->checkTerminal("OP_PTO");
    }
    else
    {
        this->throwErroProd("PA_PROG");
    }
}

void
Sintatico::Producoes::prodIdentificador()
{
    if ( this->getCurrentToken().token_class == "TO_ID" )
    {
        this->nextToken();
    }
    else
    {
        this->throwErroProd("<identificador>");
    }
}

void
Sintatico::Producoes::prodBloco()
{
    if ( this->getCurrentToken().value == "PA_VAR")
    {
        this->subprodVars();
    }

    while (this->getCurrentToken().value == "PA_PROCEDURE" ||
           this->getCurrentToken().value == "PA_FUNCTION" )
    {
        if ( this->getCurrentToken().value == "PA_PROCEDURE")
        {
            this->subprodProcedure();
        }
        else if ( this->getCurrentToken().value == "PA_FUNCTION")
        {
            this->subprodFunction();
        }

        this->checkTerminal("OP_PTVG");
    }

    if( this->getCurrentToken().value == "PA_BEGIN")
    {
        this->subprodBeginEnd();
    }
    else
    {
        this->throwErroProd("<bloco>");
    }
}

void
Sintatico::Producoes::subprodVars()
{
    this->nextToken();

    while( this->getCurrentToken().token_class == "TO_ID")
    {
        this->subprodLinhaDeclaracaoVars();
    }
}

void
Sintatico::Producoes::subprodLinhaDeclaracaoVars( bool _has_end_ptvg )
{    
    QStringList
    variaveis;

    while( this->getCurrentToken().token_class == "TO_ID")
    {
        variaveis.append(this->getCurrentToken().value);
        this->prodIdentificador();

        if (this->getCurrentToken().value == "OP_VIRG")
        {
            this->nextToken();
        }
        else if ( this->getCurrentToken().value == "OP_2PTO" )
        {
            this->nextToken();

            this->prodIdentificador();
        }
        else
        {
            this->throwErroProd(": ou ,");
        }
    }

    if ( _has_end_ptvg)
    {
        this->checkTerminal("OP_PTVG");
    }
}

void
Sintatico::Producoes::subprodProcedure( bool _has_bloco )
{
    this->checkTerminal("PA_PROCEDURE");

    this->subprodDeclaracaoSubRotina( _has_bloco );
}

void
Sintatico::Producoes::subprodFunction( bool _has_bloco )
{
    this->checkTerminal("PA_FUNCTION");

    this->subprodDeclaracaoSubRotina( false );

    this->checkTerminal("OP_2PTO");
    this->prodIdentificador();


    if ( _has_bloco )
    {
        this->checkTerminal("OP_PTVG");

        this->prodBloco();
    }
}

void
Sintatico::Producoes::subprodDeclaracaoSubRotina( bool _has_bloco )
{
    this->prodIdentificador();

    this->subprodParametrosFormais();

    if ( _has_bloco )
    {
        this->checkTerminal("OP_PTVG");

        this->prodBloco();
    }
}

void
Sintatico::Producoes::subprodParametrosFormais()
{
    if ( this->getCurrentToken().value == "OP_ABR_PAR")
    {
        this->checkTerminal("OP_ABR_PAR");

        this->subprodParametrosFormaisInterno();

        this->checkTerminal("OP_FCH_PAR");
    }
}

void
Sintatico::Producoes::subprodParametrosFormaisInterno()
{
    bool
    start = true;

    while ( start || this->getCurrentToken().value == "OP_PTVG" )
    {
        if( this->getCurrentToken().value == "OP_PTVG")
        {
            this->nextToken();
        }
        if ( this->getCurrentToken().value == "PA_VAR" )
        {
            this->nextToken();

            this->subprodLinhaDeclaracaoVars(false);
        }
        else if ( this->getCurrentToken().token_class == "TO_ID")
        {
            this->subprodLinhaDeclaracaoVars(false);
        }
        else if ( this->getCurrentToken().value == "PA_FUNCTION")
        {
            this->subprodFunction( false );
        }
        else if ( this->getCurrentToken().value == "PA_PROCEDURE")
        {
            this->subprodProcedure( false );
        }
        else
        {
            return;
        }
    }
}

void
Sintatico::Producoes::subprodBeginEnd( bool _has_end_ptvg )
{
    this->nextToken();
    this->subprodComandoSemRotulo();

    while( this->getCurrentToken().value == "OP_PTVG")
    {
        this->checkTerminal("OP_PTVG");
        this->subprodComandoSemRotulo();
    }

    this->checkTerminal("PA_END");

    if ( _has_end_ptvg )
    {
        this->checkTerminal("OP_PTVG");
    }
}

void
Sintatico::Producoes::subprodComandoSemRotulo()
{
    if ( this->getCurrentToken().token_class == "TO_ID")
    {
        if ( this->peek().value == "OP_ATRIB" )
        {
            this->prodIdentificador();
            this->checkTerminal("OP_ATRIB");

            this->subprodExpr();
        }
        else if ( this->peek().value == "OP_ABR_PAR" )
        {
            this->subprodCallFunc();
        }
        else
        {
            this->prodIdentificador();
        }
    }
    else if ( this->getCurrentToken().value == "PA_BEGIN")
    {
        this->subprodBeginEnd( false );
    }
    else if ( this->getCurrentToken().value == "PA_IF")
    {
        this->checkTerminal("PA_IF");

        this->subprodExpr();

        this->checkTerminal("PA_THEN");

        this->subprodComandoSemRotulo();

        if ( this->getCurrentToken().value == "PA_ELSE" )
        {
            this->checkTerminal("PA_ELSE");
            this->subprodComandoSemRotulo();
        }
    }
    else if ( this->getCurrentToken().value == "PA_WHILE")
    {
        this->checkTerminal("PA_WHILE");

        this->subprodExpr();
        this->checkTerminal("PA_DO");

        this->subprodComandoSemRotulo();
    }
}

void
Sintatico::Producoes::subprodExpr()
{
    this->subprodExprSimples();

    if ( this->getCurrentToken().value == "OP_IGUAL" ||
         this->getCurrentToken().value == "OP_DIFERENTE" ||
         this->getCurrentToken().value == "OP_MENOR" ||
         this->getCurrentToken().value == "OP_MENORIG" ||
         this->getCurrentToken().value == "OP_MAIORIG" ||
         this->getCurrentToken().value == "OP_MAIOR" )
    {
        this->checkTerminal( this->getCurrentToken().value );
        this->subprodExprSimples();
    }
}

void
Sintatico::Producoes::subprodExprSimples()
{
    if ( this->getCurrentToken().value == "OP_MAIS" ||
         this->getCurrentToken().value == "OP_MENOS")
    {
        this->checkTerminal( this->getCurrentToken().value );
    }

    this->subprodTermo();

    while( this->getCurrentToken().value == "OP_MAIS" ||
           this->getCurrentToken().value == "OP_MENOS" ||
           this->getCurrentToken().value == "PA_OR" )
    {
        this->checkTerminal( this->getCurrentToken().value );

        this->subprodTermo();
    }

}

void
Sintatico::Producoes::subprodTermo()
{
    this->subprodFator();

    if ( this->getCurrentToken().value == "OP_VEZES" ||
         this->getCurrentToken().value == "OP_DIV" ||
         this->getCurrentToken().value == "PA_AND")
    {
        this->checkTerminal( this->getCurrentToken().value );

        this->subprodFator();
    }
}

void
Sintatico::Producoes::subprodFator()
{
    if ( this->getCurrentToken().token_class == "TO_ID")
    {
        if ( this->peek().value == "OP_ABR_PAR")
        {
            this->subprodCallFunc();
        }
        else
        {
            this->prodIdentificador();
        }
    }
    else if ( this->getCurrentToken().token_class == "TO_IN")
    {
        this->subprodNumero();
    }
    else if ( this->getCurrentToken().value == "OP_ABR_PAR" )
    {
        this->checkTerminal("OP_ABR_PAR");
        this->subprodExpr();
        this->checkTerminal("OP_FCH_PAR");
    }
    else if ( this->getCurrentToken().value == "PA_NOT")
    {
        this->checkTerminal("PA_NOT");
        this->subprodFator();
    }
}

void
Sintatico::Producoes::subprodCallFunc()
{

    this->prodIdentificador();

    this->checkTerminal("OP_ABR_PAR");

    while ( this->getCurrentToken().value != "OP_FCH_PAR" )
    {
        this->subprodExpr();

        if (this->getCurrentToken().value == "OP_VIRG")
        {
            this->checkTerminal("OP_VIRG");
        }
    }

    this->checkTerminal("OP_FCH_PAR");
}


void
Sintatico::Producoes::subprodNumero()
{
    this->nextToken();
}

void
Sintatico::Producoes::checkTerminal( QString _terminal)
{
    if ( this->current_token == this->valores_lexico.end())
    {
        this->throwErroProd( _terminal );
    }

    if ( this->getCurrentToken().value == _terminal)
    {
        this->nextToken();
    }
    else
    {
        this->throwErroProd( _terminal );
    }
}
