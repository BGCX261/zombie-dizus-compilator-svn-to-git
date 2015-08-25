#ifndef SINTATICO_H
#define SINTATICO_H

#include "producoes.h"
#include "../lexico/token.h"

#include <QStandardItemModel>
#include <QFile>

namespace Sintatico
{
    class Analisador : protected Producoes
    {
    public:
        Analisador();

        ~Analisador();

        static Analisador*
        getInstance();

        void
        analize();

        QStandardItemModel*
        model_arvore_sintatica;

        void
        imprimeHash();

    private:

        static Analisador*
        instance;

        Tokens
        peek();

        int
        id_token;

        void
        nextToken();

        Tokens
        getCurrentToken();

        void
        throwErroProd( QString _esperado );

        void
        TransformaLexico(QString _filename = "lexico_out");
    };
}

#endif // SINTATICO_H
