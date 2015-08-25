#ifndef HASHNODE_H
#define HASHNODE_H

#include <QString>

namespace Sintatico
{

    enum HashNodeType
    {
        Parametro,
        Variavel,
        Funcao,
        Procedimento
    };

    typedef struct HashNode
    {
        int
        nivel_lexico;

        int
        id_escopo;

        int
        id;

        int
        deslocamento;

        HashNodeType
        classe;

        QString
        nome;

        QString
        retorno;

        QString
        tipo;

        int
        total_parametros;

    } HashNode;

}

#endif // HASHNODE_H
