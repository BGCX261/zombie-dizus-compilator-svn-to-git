#ifndef PRODUCOES_H
#define PRODUCOES_H

#include <string>

unsigned int
qHash( std::string _chave );

#include <QStandardItem>
#include <QMultiHash>
#include <QList>
#include <QStack>
#include <QPair>

#include "../lexico/token.h"
#include "hashnode.h"

namespace Sintatico
{
    class Producoes
    {
    public:

        Producoes();

        virtual
        ~Producoes();

        void
        prodPrograma();

        void
        prodIdentificador();

        void
        prodBloco();

        void
        subprodVars();

        void
        subprodLinhaDeclaracaoVars( bool _has_end_ptvg = true);

        void
        subprodProcedure( bool _has_bloco = true );

        void
        subprodFunction( bool _has_bloco = true );

        void
        subprodDeclaracaoSubRotina( bool _has_bloco );

        void
        subprodParametrosFormais();

        void
        subprodParametrosFormaisInterno();

        void
        subprodBeginEnd( bool _has_end_ptvg = false);

        void
        subprodComandoSemRotulo();

        void
        subprodExpr();

        void
        subprodExprSimples();

        void
        subprodTermo();

        void
        subprodFator();

        void
        subprodCallFunc();

        void
        subprodNumero();

    protected:

        QList<Tokens>
        valores_lexico;

        QMultiHash<std::string, HashNode>
        tabela_hash;

        /**
         *  O token atual é dado pela combinação do cursor_linha e do
         *  cursor_token
         */
        QList<Tokens>::iterator
        current_token;

        int
        contador_escopo;

        virtual Tokens
        peek() = 0;

        virtual void
        nextToken() = 0;

        virtual Tokens
        getCurrentToken() = 0;

    private:

        virtual void
        throwErroProd( QString _esperado ) = 0;

        void
        checkTerminal( QString _terminal );

    };
}

#endif // PRODUCOES_H
