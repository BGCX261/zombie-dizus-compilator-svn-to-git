#ifndef ANALISADORSINTATICO_H
#define ANALISADORSINTATICO_H

#include <iostream>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHash>

#include "../AnalisadorLexico/AnalisadorLexico.h"
#include "../AnalisadorLexico/LogErros.h"
#include "../AnalisadorLexico/StructToken.h"
#include "hashelement.h"
#include "hashelementvariavel.h"
#include "hashelementprocedimento.h"
#include "hashelementfuncao.h"
#include "hashelementparametroformal.h"

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(HashElement)

#define TAM_HASH 269

class ChaveHash : public std::string{};

unsigned int qHash( ChaveHash );

class AnalisadorSintatico
{
    public:
        AnalisadorSintatico( std::map<int, StructToken> );

        class erroSintatico{
            public:
                erroSintatico( std::string, unsigned int );
                std::string descricao;
        };

        QList< QHash<QString, HashElement*> > listaDeTabelasHash;

    private:
        std::map<int, StructToken> lexicoOut;

        std::map<int, StructToken>::iterator itrLexicoOut;

        QStandardItemModel* raiz;

        QStandardItem* raiz_dados;

        QHash<QString, HashElement*>* hashAtual;

        int deslocamentoAtual;

        QList<std::string> listaNomes;

        QList<HashElement*> listaHashElement;

        void startAnalise();

        QStandardItem* geraNoArvore( std::string, int, unsigned int, bool );

        void insereElementoNaHash( HashElement* );

        void printTabelaHash();

        void printArvoreSintatica();

        unsigned int levelLexico;

        QStandardItem* programa();

        QStandardItem* identificador( );

        QStandardItem* bloco( );

        QStandardItem* variaveis();

        QStandardItem* rotinas();

        QStandardItem* corpo();

        QStandardItem* comando();

        QStandardItem* comandoSemRotulo();

        QStandardItem* numero();

        QStandardItem* atribuicao();

        QStandardItem* chamadaDeProcedimento();

        QStandardItem* desvio();

        QStandardItem* composto();

        QStandardItem* condicional();

        QStandardItem* repetitivo();

        QStandardItem* expressao();

        QStandardItem* listaDeExpressoes();

        QStandardItem* variavel();

        QStandardItem* listaDeIdentificadores();

        QStandardItem* tipo();

        QStandardItem* operadorMultiplicativo();

        QStandardItem* operadorAditivo();

        QStandardItem* termo();

        QStandardItem* expressaoSimples();

        QStandardItem* operadorRelacional();

        QStandardItem* fator();

        QStandardItem* chamadaDeFuncao();

        QStandardItem* parametroExpressao();

        QStandardItem* parametroFormal();

        QStandardItem* parametrosFormais();

        QStandardItem* funcao();

        QStandardItem* procedimento();

};

#endif // ANALISADORSINTATICO_H
