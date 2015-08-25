#include "sintatico.h"

#include <QDebug>
#include <QTreeView>
#include <QApplication>


#include "errosintatico.h"

Sintatico::Analisador*
Sintatico::Analisador::instance = 0;

Sintatico::Analisador::Analisador()
{
    this->TransformaLexico();

    this->current_token = this->valores_lexico.begin();

    this->id_token = 0;
    this->contador_escopo = 0;
}

Sintatico::Analisador::~Analisador()
{

}

Sintatico::Analisador*
Sintatico::Analisador::getInstance()
{
    if (Sintatico::Analisador::instance == 0)
    {
        Sintatico::Analisador::instance = new Analisador();
    }

    return Sintatico::Analisador::instance;
}

void
Sintatico::Analisador::analize()
{
    try
    {
        this->prodPrograma();
    }
    catch (ErroSintatico erro)
    {

    }

//    int teste = 1;
//    char* teste_v[1];
//
//    teste_v[0] = "bla";
//
//    QApplication
//    app(teste,teste_v);
//
//    QTreeView
//    view;
//
//    view.setModel(this->model_arvore_sintatica);
//
//    view.show();
//
//    app.exec();
}

/**
 *
 * Retorna o proximo nó sem visita-lo.
 */
Tokens
Sintatico::Analisador::peek()
{
    this->current_token++;

    Tokens
    ret = this->getCurrentToken();

    this->current_token--;

    return ret;
}

/**
 *
 * seta o atributo cursor_token para o próximo token e o retorna.
 */
void
Sintatico::Analisador::nextToken()
{
    this->id_token++;
    this->current_token++;
}

Tokens
Sintatico::Analisador::getCurrentToken()
{
    return *(this->current_token);
}

void
Sintatico::Analisador::throwErroProd( QString _esperado )
{
    qDebug() << "Linha: " << this->getCurrentToken().linha
             << " Simbolo nao esperado encontrado: "
             << this->getCurrentToken().value;

//    exit(1);
}

void
Sintatico::Analisador::TransformaLexico(QString _filename)
{
    QFile
    arquivo;
    arquivo.setFileName(_filename);
    arquivo.open(QIODevice::ReadOnly);

    QTextStream tsFile(&arquivo);
    while(!tsFile.atEnd()){
        QString line = tsFile.readLine();
        //remove o nome do arquivo
        while(line[0]!=':'){
            line.remove(0,1);
        }
        line.remove(0,1);
        //tranforma string em Stream
        QTextStream tsLine(&line,QIODevice::ReadOnly);
        //Contador de linhas
        int lineCount;
        //le o numero da linha
        tsLine>>lineCount;
        //remove caracteres de controle
        line.remove(0,2);
        line.replace(',',' ');
        line.replace('[',' ');
        line.replace(']',' ');
        //lê os tokens
        while(!tsLine.atEnd()){
        //remove '['
            Tokens temp;
            temp.linha = lineCount;
            tsLine>>temp.token_class;
            tsLine>>temp.value;
            if(!temp.value.isEmpty()){
                this->valores_lexico.append(temp);
//                qDebug()<<temp.value<<" - "<<temp.token_class;
            }
        }

    }
}

void
Sintatico::Analisador::imprimeHash() {
    QMultiHash<std::string, Sintatico::HashNode>::iterator cursor;

    QFile
    saida_hash;
    saida_hash.setFileName("saida_hash.txt");
    saida_hash.open(QIODevice::WriteOnly);

    QTextStream
    saida_stream(&saida_hash);

    cursor = this->tabela_hash.begin();

    while((cursor != this->tabela_hash.end())) {

        QString classe;
        switch((*(cursor)).classe) {
            case Sintatico::Funcao:
                classe = "FUNCAO";
            break;
            case Sintatico::Procedimento:
                classe = "PROCEDIMENTO";
            break;
            case Sintatico::Parametro:
                classe = "PARAMETRO";
            break;
            case Sintatico::Variavel:
                classe = "VARIAVEL";
            break;
        }

        saida_stream << " Classe: " << classe << '\n';
        saida_stream << " Nome: " << (*(cursor)).nome << '\n';
        saida_stream << " Nivel Lexico: " << (*(cursor)).nivel_lexico << '\n';
        saida_stream << " Deslocamento: " << (*(cursor)).deslocamento << '\n';

        switch((*(cursor)).classe)
        {
        case Sintatico::Funcao:
            saida_stream << "Retorno: " << (*(cursor)).retorno;
            break;
        case Sintatico::Variavel:
        case Sintatico::Parametro:
            saida_stream << "Tipo: " << (*(cursor)).tipo;
            break;
        }

        cursor++;
    }

    saida_hash.close();
    QFile::remove("saida_hash.txt");
}
