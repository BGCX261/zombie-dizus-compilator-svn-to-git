#include <QtGui>
#include "AnalisadorSintatico.h"

AnalisadorSintatico::AnalisadorSintatico( std::map<int, StructToken> _lexicoOut )
{
    this->lexicoOut = _lexicoOut;
    this->itrLexicoOut = this->lexicoOut.begin( );
    this->levelLexico = 0;
    this->raiz = new QStandardItemModel();

    this->startAnalise( );
    this->printTabelaHash( );
    this->printArvoreSintatica( );
}

unsigned int qHash( ChaveHash w )
{
    int h = 0;

    //auxiliar dos caracteres. armazena o ASCII de cada caracter de w
    int numWord;

    int alfa = 23;

    //Faz a conta do
    for (int i = 0; i < w.capacity(); i++)
    {
        numWord = (int) w[i];
       
        //alfa é uma constante usada na multiplicação. Eu usei 5
        h = h*alfa + numWord;
    }

    //resto de h / M
    h = h % TAM_HASH;

    return h;
} 

AnalisadorSintatico::erroSintatico::erroSintatico( std::string _descricao, unsigned int _linha )
{
    this->descricao = _descricao;
    std::cout << " " + _linha << std::endl;
}

void AnalisadorSintatico::startAnalise()
{
    try{
        this->raiz_dados = this->programa();
    }
    catch( AnalisadorSintatico::erroSintatico &erro )
    {
        std::cout << "\nrolou um erro na pegada! " + erro.descricao << std::endl;
        exit(1);
    }

}

void AnalisadorSintatico::insereElementoNaHash( HashElement* _elemento )
{
    if( !this->hashAtual->contains( _elemento->identificador.c_str() ) )
    {
        this->hashAtual->insert( _elemento->identificador.c_str(), _elemento );
    }
//    else
//    {
//        throw erroSintatico( "Redefinicao: " + _elemento->identificador + " ja existe.", this->itrLexicoOut->second.linha );
//    }

    if( this->hashAtual->contains( _elemento->identificador.c_str() ))
    {
        if( this->hashAtual->value( _elemento->identificador.c_str() )->classificacao == "[VARIAVEL]" )
        {
            std::cout << "Identificador:" << this->hashAtual->value( _elemento->identificador.c_str() )->identificador << std::endl;
            std::cout << "Classificacao:" << this->hashAtual->value( _elemento->identificador.c_str() )->classificacao << std::endl;
            std::cout << "Nivel Lexico: " << this->hashAtual->value( _elemento->identificador.c_str() )->levelLexico << std::endl;
            std::cout << "Tipo: " << this->hashAtual->value( _elemento->identificador.c_str() )->tipo << std::endl;
            std::cout << "Deslocamento: " << this->hashAtual->value( _elemento->identificador.c_str() )->deslocamento << std::endl;

        }
        else if( this->hashAtual->value( _elemento->identificador.c_str() )->classificacao == "[PARAMETRO_FORMAL]" )
        {
            std::cout << "Identificador:" << this->hashAtual->value( _elemento->identificador.c_str() )->identificador << std::endl;
            std::cout << "Classificacao:" << this->hashAtual->value( _elemento->identificador.c_str() )->classificacao << std::endl;
            std::cout << "Nivel Lexico: " << this->hashAtual->value( _elemento->identificador.c_str() )->levelLexico << std::endl;
            std::cout << "Tipo: " << this->hashAtual->value( _elemento->identificador.c_str() )->tipo << std::endl;
            std::cout << "Deslocamento: " << this->hashAtual->value( _elemento->identificador.c_str() )->deslocamento << std::endl;
            std::cout << "Passagem: " << this->hashAtual->value( _elemento->identificador.c_str() )->passagem << std::endl;
        }
        else if( this->hashAtual->value( _elemento->identificador.c_str() )->classificacao == "[PROCEDIMENTO]" )
        {
            std::cout << "Identificador:" << this->hashAtual->value( _elemento->identificador.c_str() )->identificador << std::endl;
            std::cout << "Classificacao:" << this->hashAtual->value( _elemento->identificador.c_str() )->classificacao << std::endl;
            std::cout << "Nivel Lexico: " << this->hashAtual->value( _elemento->identificador.c_str() )->levelLexico << std::endl;
            std::cout << "Deslocamento: " << this->hashAtual->value( _elemento->identificador.c_str() )->deslocamento << std::endl;
            std::cout << "Quantidade de Parametros: " << this->hashAtual->value( _elemento->identificador.c_str() )->qdeParametros << std::endl;

            for( int i = 0; i < this->hashAtual->value( _elemento->identificador.c_str() )->parametros->size(); i++ )
            {
                std::cout << "\n\t\t**Parametro " + i << std::endl;
                std::cout << "Identificador:" << this->hashAtual->value( _elemento->identificador.c_str() )->parametros->value(i);
            }
        }
        else if( this->hashAtual->value( _elemento->identificador.c_str() )->classificacao == "[FUNCAO]" )
        {
            std::cout << "Identificador:" << this->hashAtual->value( _elemento->identificador.c_str() )->identificador << std::endl;
            std::cout << "Classificacao:" << this->hashAtual->value( _elemento->identificador.c_str() )->classificacao << std::endl;
            std::cout << "Nivel Lexico: " << this->hashAtual->value( _elemento->identificador.c_str() )->levelLexico << std::endl;
            std::cout << "Deslocamento: " << this->hashAtual->value( _elemento->identificador.c_str() )->deslocamento << std::endl;
            std::cout << "Quantidade de Parametros: " << this->hashAtual->value( _elemento->identificador.c_str() )->qdeParametros << std::endl;

            for( int i = 0; i < this->hashAtual->value( _elemento->identificador.c_str() )->parametros->size(); i++ )
            {
                std::cout << "\n\t\t**Parametro " + i << std::endl;
                std::cout << "Identificador:" << this->hashAtual->value( _elemento->identificador.c_str() )->parametros->value(i);
            }

            std::cout << "Retorno: " << this->hashAtual->value( _elemento->identificador.c_str() )->retorno << std::endl;
        }

        std::cout << "\n#########################################################" << std::endl;

    }
}

void AnalisadorSintatico::printTabelaHash( )
{
    std::cout << " " + this->hashAtual->capacity() << std::endl;
}

void AnalisadorSintatico::printArvoreSintatica( )
{
    int param_1 = 1;
    char *param_2[1];

    param_2[0] = "x";

    QApplication app(param_1, param_2);

    QTreeView view;
    view.setModel( this->raiz );
    view.setWindowTitle(QObject::tr("Arvore Sintatica Abstrata"));
    view.show();

    app.exec();
}

QStandardItem *AnalisadorSintatico::geraNoArvore( std::string _descricao, int _levelLexico, unsigned int _linha, bool _isTerminal ){

    QList<QVariant>
    listaDadosNo;

    QVariant
    descricao;

    QVariant
    levelLexico;

    QVariant
    linha;

    QVariant
    isTerminal;

    descricao.setValue( _descricao );
    levelLexico.setValue( _levelLexico );
    linha.setValue( _linha );
    isTerminal.setValue( _isTerminal );

    listaDadosNo.append( descricao );
    listaDadosNo.append( levelLexico );
    listaDadosNo.append( linha );
    listaDadosNo.append( isTerminal );

    QStandardItem* item = new QStandardItem( QString( descricao.value<std::string>().c_str() ) );

    return item;

}

QStandardItem* AnalisadorSintatico::programa( )
{

    this->deslocamentoAtual = 0;

    QStandardItem* _raiz = this->raiz->invisibleRootItem();

    QHash<QString, HashElement*> _hashPrograma;

    this->listaDeTabelasHash.append(_hashPrograma);

    this->hashAtual = &_hashPrograma;

    _raiz->appendRow( this->geraNoArvore( "<PROGRAMA>", this->levelLexico, this->itrLexicoOut->second.linha, false ) );

    if( this->itrLexicoOut->second.token == "program" )
    {

        _raiz->appendRow(this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
        this->itrLexicoOut++;

    }
    else
    {
        throw erroSintatico("Programa: Esperado program", this->itrLexicoOut->second.linha );
    }

    _raiz->appendRow( this->identificador() );

    if( this->itrLexicoOut->second.token == ";")
    {
        _raiz->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

    }
    else
    {
        throw erroSintatico("Programa: Esperado ;", this->itrLexicoOut->second.linha );
    }

    _raiz->appendRow( this->bloco() );

    if( this->itrLexicoOut->second.token == "." )
    {
        _raiz->appendRow(this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true  ));
    }
    else
    {
        throw erroSintatico("Programa: Esperado .", this->itrLexicoOut->second.linha );
    }

    return _raiz;

}

QStandardItem* AnalisadorSintatico::identificador( )
{
    QStandardItem* identificador = 0;

    if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        identificador = this->geraNoArvore( "<IDENTIFICADOR>", this->levelLexico, this->itrLexicoOut->second.linha, false  );
        identificador->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true));
        this->itrLexicoOut++;
    }
    else
    {
        throw erroSintatico("Identificador: Esperado identificador.", this->itrLexicoOut->second.linha );
    }

    return identificador;
}

QStandardItem* AnalisadorSintatico::bloco( )
{
    QStandardItem* bloco;

    bloco = this->geraNoArvore( "<BLOCO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    /* OPCIONAL */
    QStandardItem* testeRetornoVariaveis = this->variaveis();

    if( testeRetornoVariaveis != 0 )
    {
        bloco->appendRow( testeRetornoVariaveis );
    }

    while( this->itrLexicoOut->second.token == "function" || this->itrLexicoOut->second.token == "procedure" )
    {
        bloco->appendRow( this->rotinas() );
    }

    /* OBRIGATORIO */
    if( this->itrLexicoOut->second.token == "begin" )
    {
        bloco->appendRow( this->composto() );
    }
    else
    {
        throw erroSintatico( "Bloco: Esperado begin", this->itrLexicoOut->second.linha );
    }

    return bloco;

}

QStandardItem* AnalisadorSintatico::variaveis()
{
    QStandardItem* variaveis = 0;

    int _deslocamentoAtual = 0;

    if( this->itrLexicoOut->second.token == "var")
    {
        variaveis = this->geraNoArvore( "<VARIAVEIS>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        variaveis->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
        {
            while( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR")
            {
                variaveis->appendRow( this->listaDeIdentificadores() );

                if( this->itrLexicoOut->second.token == ":")
                {
                    variaveis->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
                    this->itrLexicoOut++;
                }
                else
                {
                    throw erroSintatico("Variaveis: Esperado :", this->itrLexicoOut->second.linha);
                }

                for( int i = 0; i < this->listaNomes.size(); i++ )
                {
                    HashElementVariavel _variavelAtual;

                    this->listaHashElement.append(&_variavelAtual);

                    _variavelAtual.identificador = this->listaNomes[i];
                    _variavelAtual.classificacao = "[VARIAVEL]";
                    _variavelAtual.deslocamento = _deslocamentoAtual++;
                    _variavelAtual.levelLexico = this->levelLexico;
                    _variavelAtual.tipo = this->itrLexicoOut->second.token;

                    this->insereElementoNaHash(&_variavelAtual);

                }
                variaveis->appendRow( this->tipo() );


                if( this->itrLexicoOut->second.token == ";" )
                {
                    variaveis->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
                    this->itrLexicoOut++;
                }
                else
                {
                    throw erroSintatico( "variaveis: Esperado ;", this->itrLexicoOut->second.linha );
                }

                this->listaNomes.clear();
                
            }
        }
        else
        {
            throw erroSintatico( "Variaveis: Esperado IDENTIFICADOR", this->itrLexicoOut->second.linha );
        }

    }

    this->listaNomes.clear();

    return variaveis;
}

QStandardItem* AnalisadorSintatico::rotinas()
{
    QStandardItem* rotinas = 0;

    this->deslocamentoAtual = 0;

    if( this->itrLexicoOut->second.token == "function" )
    {
        rotinas = this->geraNoArvore( "<ROTINA>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        QStandardItem* testeRetornoFuncao;

        testeRetornoFuncao = this->funcao();

        if( testeRetornoFuncao != 0 )
        {
            rotinas->appendRow( testeRetornoFuncao );
        }
    }
    else if( this->itrLexicoOut->second.token == "procedure" )
    {
        rotinas = this->geraNoArvore( "<ROTINA>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        QStandardItem* testeRetornoProcedimento;

        testeRetornoProcedimento = this->procedimento();

        if( testeRetornoProcedimento != 0 )
        {
            rotinas->appendRow( testeRetornoProcedimento );
        }
    }

    return rotinas;
}

QStandardItem* AnalisadorSintatico::corpo()
{
    QStandardItem* corpo;

    corpo = this->geraNoArvore( "<CORPO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    corpo->appendRow( this->comandoSemRotulo() );

    return corpo;
}

QStandardItem* AnalisadorSintatico::comando()
{
    QStandardItem* comando = 0;

    if( this->itrLexicoOut->second.token != "end" )
    {
        comando = this->geraNoArvore( "<COMANDO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        comando->appendRow( this->comandoSemRotulo() );
    }
    else
    {
        throw erroSintatico( "Comando: end nao pode iniciar um comando", this->itrLexicoOut->second.linha );
    }
    return comando;
}

QStandardItem* AnalisadorSintatico::comandoSemRotulo()
{
    QStandardItem* comandoSemRotulo = geraNoArvore( "<COMANDO_SEM_ROTULO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    if( this->itrLexicoOut->second.token == "if" )
    {
        comandoSemRotulo->appendRow( this->condicional() );
    }
    else if( this->itrLexicoOut->second.token == "while" )
    {
        comandoSemRotulo->appendRow( this->repetitivo() );
    }
    else if( this->itrLexicoOut->second.token == "begin" )
    {
        comandoSemRotulo->appendRow( this->composto() );
    }
    else if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        std::map<int, StructToken>::iterator itrTeste;
        itrTeste = this->itrLexicoOut;
        itrTeste++;

        if( itrTeste->second.token == "(" )
        {
            comandoSemRotulo->appendRow( this->chamadaDeProcedimento() );
        }
        else if( itrTeste->second.token == ":=" )
        {
            comandoSemRotulo->appendRow( this->atribuicao() );
        }
    }

    return comandoSemRotulo;
}

QStandardItem* AnalisadorSintatico::numero()
{
    QStandardItem* numero = 0;

    if( this->itrLexicoOut->second.classificacao == "NUMERO" )
    {
        numero = geraNoArvore( "<NUMERO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        numero->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
        this->itrLexicoOut++;
    }

    return numero;
}

QStandardItem* AnalisadorSintatico::atribuicao()
{
    QStandardItem* atribuicao = 0;

    if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        std::map<int, StructToken>::iterator itrProximoToken;
        itrProximoToken = this->itrLexicoOut;
        itrProximoToken++;

        if( itrProximoToken->second.token == ":=" )
        {
            atribuicao = this->geraNoArvore("<ATRIBUICAO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

            atribuicao->appendRow( this->variavel() );

            if( this->itrLexicoOut->second.token == ":=" )
            {
                atribuicao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
                this->itrLexicoOut++;
            }
            else
            {
                throw erroSintatico( "Atribuicao: Esperado :=", this->itrLexicoOut->second.linha );
            }
            atribuicao->appendRow( this->expressao() );
        }
    }

    return atribuicao;
}

QStandardItem* AnalisadorSintatico::chamadaDeProcedimento()
{
    QStandardItem* chamadaDeProcedimento = 0;

    if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        std::map<int, StructToken>::iterator itrProximoToken;
        itrProximoToken = this->itrLexicoOut;
        itrProximoToken++;

        if( itrProximoToken->second.token == "(" )
        {
            chamadaDeProcedimento = this->geraNoArvore("<CHAMADA_DE_PROCEDIMENTO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

            chamadaDeProcedimento->appendRow( this->identificador() );

            chamadaDeProcedimento->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;

            if( this->itrLexicoOut->second.token != ")" )
            {
                chamadaDeProcedimento->appendRow( this->listaDeExpressoes() );
            }

            if( this->itrLexicoOut->second.token == ")")
            {
                chamadaDeProcedimento->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
                this->itrLexicoOut++;
            }
            else
            {
                throw erroSintatico("ChamadaDeProcedimento: Esperado )", this->itrLexicoOut->second.linha );
            }

        }
    }

    return chamadaDeProcedimento;
}

QStandardItem* AnalisadorSintatico::composto()
{
    QStandardItem* composto = 0;
    
    if( this->itrLexicoOut->second.token == "begin" )
    {
        composto = this->geraNoArvore( "<COMPOSTO>", this->levelLexico, this->itrLexicoOut->second.linha, false );
        
        composto->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        composto->appendRow( this->comandoSemRotulo() );

        while( this->itrLexicoOut->second.token == ";" )
        {
            composto->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
            this->itrLexicoOut++;

            if( this->itrLexicoOut->second.token != "end")
            {
                composto->appendRow( this->comandoSemRotulo() );
            }
        }

        if( this->itrLexicoOut->second.token == "end" ){
            composto->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Composto: Esperado ;", this->itrLexicoOut->second.linha );
        }
    }
    
    return composto;
}

QStandardItem* AnalisadorSintatico::condicional()
{
    QStandardItem* condicional = 0;

    if( this->itrLexicoOut->second.token == "if" )
    {
        condicional = this->geraNoArvore( "<CONDICIONAL>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        condicional->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        condicional->appendRow( this->expressao() );

        if( this->itrLexicoOut->second.token == "then" )
        {
            condicional->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Condicional: Esperado then", this->itrLexicoOut->second.linha );
        }

        condicional->appendRow( this->comandoSemRotulo() );

        if( this->itrLexicoOut->second.token == "else" )
        {
            condicional->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true  ));
            this->itrLexicoOut++;

            condicional->appendRow( this->comandoSemRotulo() );
        }

    }
    return condicional;
}

QStandardItem* AnalisadorSintatico::repetitivo()
{
    QStandardItem* repetitivo = 0;

    if( this->itrLexicoOut->second.token == "while" )
    {
        repetitivo = this->geraNoArvore( "<REPETITIVO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        repetitivo->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        repetitivo->appendRow( this->expressao() );

        if( this->itrLexicoOut->second.token == "do" )
        {
            repetitivo->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Repetitivo: Esperado do", this->itrLexicoOut->second.linha );
        }

        repetitivo->appendRow( this->comandoSemRotulo() );
    }

    return repetitivo;
}

QStandardItem* AnalisadorSintatico::expressao()
{
    QStandardItem* expressao;

    expressao = this->geraNoArvore( "<EXPRESSAO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    expressao->appendRow( this->expressaoSimples() );

    if( this->itrLexicoOut->second.classificacao == "OPERADOR_RELACIONAL" )
    {
        expressao->appendRow( this->operadorRelacional() );

        expressao->appendRow( this->expressaoSimples() );
    }

    return expressao;
}

QStandardItem* AnalisadorSintatico::listaDeExpressoes()
{
    QStandardItem* listaDeExpressoes = 0;

    listaDeExpressoes = this->geraNoArvore( "<LISTA_DE_EXPRESSOES>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    listaDeExpressoes->appendRow( this->expressao() );

    while( this->itrLexicoOut->second.token == "," )
    {
        listaDeExpressoes->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ));
        this->itrLexicoOut++;

        listaDeExpressoes->appendRow( this->expressao() );
    }

    return listaDeExpressoes;
}

QStandardItem* AnalisadorSintatico::variavel()
{
    QStandardItem* variavel = 0;

    if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        variavel = this->geraNoArvore( "<VARIAVEL>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        variavel->appendRow( this->identificador() );
    }

    return variavel;
}

QStandardItem* AnalisadorSintatico::tipo()
{
    QStandardItem* tipo = this->geraNoArvore( "<TIPO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    tipo->appendRow( this->identificador() );

    return tipo;
}

QStandardItem* AnalisadorSintatico::listaDeIdentificadores()
{
    QStandardItem* listaDeIdentificadores;

    listaDeIdentificadores = this->geraNoArvore( "<LISTA_DE_IDENTIFICADORES>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    this->listaNomes.append( this->itrLexicoOut->second.token );

    listaDeIdentificadores->appendRow( this->identificador() );

    while( this->itrLexicoOut->second.token == "," )
    {
        listaDeIdentificadores->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        this->listaNomes.append( this->itrLexicoOut->second.token );

        listaDeIdentificadores->appendRow( this->identificador() );
    }

    return listaDeIdentificadores;
}

QStandardItem* AnalisadorSintatico::expressaoSimples()
{
    QStandardItem* expressaoSimples;

    expressaoSimples = this->geraNoArvore( "<EXPRESSAO_SIMPLES>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    if( this->itrLexicoOut->second.token == "+" || this->itrLexicoOut->second.token == "-" )
    {
        expressaoSimples->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }

    expressaoSimples->appendRow( this->termo() );

    while( this->itrLexicoOut->second.token == "+" || this->itrLexicoOut->second.token == "-" || this->itrLexicoOut->second.token == "or" )
    {
        expressaoSimples->appendRow( this->operadorAditivo() );
        expressaoSimples->appendRow( this->termo() );
    }

    return expressaoSimples;
}

QStandardItem* AnalisadorSintatico::termo()
{
    QStandardItem* termo;

    termo = this->geraNoArvore( "<TERMO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    termo->appendRow( this->fator() );

    while( this->itrLexicoOut->second.token == "*" || this->itrLexicoOut->second.token == "div" || this->itrLexicoOut->second.token == "and" )
    {
        termo->appendRow( this->operadorMultiplicativo() );

        termo->appendRow( this->fator() );
    }

    return termo;
}

QStandardItem* AnalisadorSintatico::operadorAditivo()
{
    QStandardItem* operadorAditivo = 0;

    if( this->itrLexicoOut->second.token == "+" || this->itrLexicoOut->second.token == "-" || this->itrLexicoOut->second.token == "or" )
    {
        operadorAditivo = this->geraNoArvore( "<OPERADOR_ADITIVO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        operadorAditivo->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }

    return operadorAditivo;
}

QStandardItem* AnalisadorSintatico::operadorMultiplicativo()
{
    QStandardItem* operadorMultiplicativo = 0;

    if( this->itrLexicoOut->second.token == "*" || this->itrLexicoOut->second.token == "div" || this->itrLexicoOut->second.token == "and" )
    {
        operadorMultiplicativo = this->geraNoArvore( "<OPERADOR_MULTIPLICATIVO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        operadorMultiplicativo->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }

    return operadorMultiplicativo;
}

QStandardItem* AnalisadorSintatico::fator()
{
    QStandardItem* fator = 0;

    if( this->itrLexicoOut->second.token == "(" )
    {
        fator = this->geraNoArvore( "<FATOR>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        fator->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        fator->appendRow( this->expressao() );

        if( this->itrLexicoOut->second.token == ")" )
        {
            fator->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Fator: Esperado )", this->itrLexicoOut->second.linha );
        }
    }
    else if( this->itrLexicoOut->second.token == "not")
    {
        fator = this->geraNoArvore( "<FATOR>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        fator->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        fator->appendRow( this->fator() );
    }
    else if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        fator = this->geraNoArvore( "<FATOR>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        std::map<int, StructToken>::iterator itrTeste;
        itrTeste = this->itrLexicoOut;
        itrTeste++;

        if( itrTeste->second.token == "(" )
        {
            fator->appendRow( this->chamadaDeFuncao() );
        }
        else
        {
            fator->appendRow( this->variavel() );
        }
    }
    else if( this->itrLexicoOut->second.classificacao == "NUMERO" )
    {
        fator = this->geraNoArvore( "<FATOR>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        fator->appendRow( this->numero() );
    }

    if( fator == 0 )
    {
        throw erroSintatico( "Fator: erro ", this->itrLexicoOut->second.linha );
    }
    return fator;

}

QStandardItem* AnalisadorSintatico::operadorRelacional()
{
    QStandardItem* operadorRelacional = 0;

    if( this->itrLexicoOut->second.classificacao == "OPERADOR_RELACIONAL" )
    {
        operadorRelacional = this->geraNoArvore( "<OPERADOR_RELACIONAL>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        operadorRelacional->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }

    return operadorRelacional;
}

QStandardItem* AnalisadorSintatico::chamadaDeFuncao()
{
    QStandardItem* chamadaDeFuncao = 0;

    if( this->itrLexicoOut->second.classificacao == "IDENTIFICADOR" )
    {
        chamadaDeFuncao = this->geraNoArvore( "<CHAMADA_DE_FUNCAO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        chamadaDeFuncao->appendRow( this->identificador() );

        if( this->itrLexicoOut->second.token == "(" )
        {
            chamadaDeFuncao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;

            if( this->itrLexicoOut->second.token != ")" )
            {
                chamadaDeFuncao->appendRow( this->listaDeExpressoes() );
            }

            if ( this->itrLexicoOut->second.token == ")" ){
                chamadaDeFuncao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
                this->itrLexicoOut++;
            }
            else
            {
                throw erroSintatico( "ChamadaDeFuncao: Esperado )", this->itrLexicoOut->second.linha );
            }
        }

    }
    return chamadaDeFuncao;
}

QStandardItem* AnalisadorSintatico::funcao()
{
    QStandardItem* funcao = 0;

    unsigned int _guardaLevelLexicoAnterior = this->levelLexico;

    this->levelLexico++;

    QHash<QString, HashElement*>* _guardaHashAtual = this->hashAtual;

    this->hashAtual = new QHash<QString, HashElement*>();

    this->listaDeTabelasHash.append(*this->hashAtual);

    HashElement _funcaoAtual;

    this->listaHashElement.append(&_funcaoAtual);

    if( this->itrLexicoOut->second.token == "function" )
    {
        funcao = this->geraNoArvore( "<FUNCAO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        funcao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        _funcaoAtual.identificador = this->itrLexicoOut->second.token;
        _funcaoAtual.classificacao = "[FUNCAO]";
        _funcaoAtual.deslocamento = this->deslocamentoAtual;
        _funcaoAtual.levelLexico = _guardaLevelLexicoAnterior;
        _funcaoAtual.hash = this->hashAtual;

        funcao->appendRow( this->identificador() );

        this->deslocamentoAtual = 0;

        std::map<int, StructToken>::iterator _proxSimbolo = this->itrLexicoOut;

        _proxSimbolo++;

        if( _proxSimbolo->second.token == "var" )
        {
            _funcaoAtual.passagem = "parametro";
        }
        else
        {
            _funcaoAtual.passagem = "referencia";
        }

        funcao->appendRow( this->parametrosFormais() );

        _funcaoAtual.parametros = &this->listaNomes;
        _funcaoAtual.qdeParametros = this->listaNomes.size();

        if( this->itrLexicoOut->second.token == ":" )
        {
            funcao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Funcao: Esperado :", this->itrLexicoOut->second.linha );
        }

        _funcaoAtual.retorno = this->itrLexicoOut->second.token;

        funcao->appendRow( this->identificador() );

        if( this->itrLexicoOut->second.token == ";" )
        {
            funcao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Funcao: Esperado ;", this->itrLexicoOut->second.linha );
        }

        this->deslocamentoAtual = 0;

        funcao->appendRow( this->bloco() );

        if( this->itrLexicoOut->second.token == ";" )
        {
            funcao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Funcao: Esperado ;", this->itrLexicoOut->second.linha );
        }
    }

    this->insereElementoNaHash(&_funcaoAtual);

    this->listaNomes.clear();

    this->hashAtual = _guardaHashAtual;

    this->levelLexico = _guardaLevelLexicoAnterior;

    return funcao;
}

QStandardItem* AnalisadorSintatico::procedimento()
{
    QStandardItem* procedimento = 0;

    unsigned int _guardaLevelLexicoAnterior = this->levelLexico++;

    QHash<QString, HashElement*>* _guardaHashAtual = this->hashAtual;

    this->hashAtual = new QHash<QString, HashElement*>();

    this->listaDeTabelasHash.append(*this->hashAtual);

    HashElement _procedimentoAtual;

    this->listaHashElement.append(&_procedimentoAtual);

    if( this->itrLexicoOut->second.token == "procedure" )
    {
        procedimento = this->geraNoArvore( "<PROCEDIMENTO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        procedimento->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;

        _procedimentoAtual.identificador = this->itrLexicoOut->second.token;
        _procedimentoAtual.classificacao = "[PROCEDIMENTO]";
        _procedimentoAtual.deslocamento = this->deslocamentoAtual;
        _procedimentoAtual.levelLexico = _guardaLevelLexicoAnterior;
        _procedimentoAtual.hash = this->hashAtual;

        procedimento->appendRow( this->identificador() );

        this->deslocamentoAtual = 0;

        std::map<int, StructToken>::iterator _proxSimbolo = this->itrLexicoOut;

        _proxSimbolo++;

        if( _proxSimbolo->second.token == "var" )
        {
            _procedimentoAtual.passagem = "parametro";
        }
        else
        {
            _procedimentoAtual.passagem = "referencia";
        }

        procedimento->appendRow( this->parametrosFormais() );

        _procedimentoAtual.parametros = &this->listaNomes;
        _procedimentoAtual.qdeParametros = this->listaNomes.size();

        if( this->itrLexicoOut->second.token == ";" )
        {
            procedimento->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Procedimento: Esperado ;", this->itrLexicoOut->second.linha );
        }

        this->deslocamentoAtual = 0;

        procedimento->appendRow( this->bloco() );

        if( this->itrLexicoOut->second.token == ";" )
        {
            procedimento->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;
        }
        else
        {
            throw erroSintatico( "Procedimento: Esperado ;", this->itrLexicoOut->second.linha );
        }
    }

    this->insereElementoNaHash(&_procedimentoAtual);

    this->listaNomes.clear();

    this->hashAtual = _guardaHashAtual;

    this->levelLexico = _guardaLevelLexicoAnterior;

    return procedimento;
}

QStandardItem* AnalisadorSintatico::parametrosFormais()
{
    QStandardItem* parametrosFormais;

    if( this->itrLexicoOut->second.token == "(" )
    {
        parametrosFormais = this->geraNoArvore( "<PARAMETROS_FORMAIS>", this->levelLexico, this->itrLexicoOut->second.linha, false );

        parametrosFormais->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }
    else
    {
        throw erroSintatico( "ParametrosFormais: Esperado (", this->itrLexicoOut->second.linha );
    }

    if( this->itrLexicoOut->second.token != ")" )
    {
        parametrosFormais->appendRow( this->parametroFormal() );

        while( this->itrLexicoOut->second.token == ";" )
        {
            parametrosFormais->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
            this->itrLexicoOut++;

            parametrosFormais->appendRow( this->parametroFormal() );
        }

        parametrosFormais->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }
    else
    {
        parametrosFormais->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }

    return parametrosFormais;
}

QStandardItem* AnalisadorSintatico::parametroFormal()
{
    QStandardItem* parametroFormal;

    parametroFormal = this->geraNoArvore( "<PARAMETRO_FORMAL>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    parametroFormal->appendRow( this->parametroExpressao() );

    return parametroFormal;
}

QStandardItem* AnalisadorSintatico::parametroExpressao()
{
    QStandardItem* parametroExpressao;

    std::string _passagem;

    parametroExpressao = this->geraNoArvore( "<PARAMETRO_EXPRESSAO>", this->levelLexico, this->itrLexicoOut->second.linha, false );

    if( this->itrLexicoOut->second.token == "var" )
    {

        parametroExpressao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
        _passagem = "Parametro";

    }
    else
    {
        _passagem = "Referencia";
    }

    parametroExpressao->appendRow( this->listaDeIdentificadores() );

    if( this->itrLexicoOut->second.token == ":" )
    {
        parametroExpressao->appendRow( this->geraNoArvore( this->itrLexicoOut->second.token, this->levelLexico, this->itrLexicoOut->second.linha, true ) );
        this->itrLexicoOut++;
    }
    else
    {
        throw erroSintatico( "ParametroExpressao: Esperado :", this->itrLexicoOut->second.linha );
    }

    for( int i = 0; i < this->listaNomes.size(); i++ )
    {
        HashElement _elementoAtual;

        this->listaHashElement.append(&_elementoAtual);

        _elementoAtual.identificador = this->listaNomes[i];
        _elementoAtual.classificacao = "[PARAMETRO_FORMAL]";
        _elementoAtual.deslocamento = this->deslocamentoAtual++;
        _elementoAtual.levelLexico = this->levelLexico;
        _elementoAtual.tipo = this->itrLexicoOut->second.token;
        _elementoAtual.passagem = _passagem;

        this->insereElementoNaHash(&_elementoAtual);
    }

    parametroExpressao->appendRow( this->identificador() );

    return parametroExpressao;
}
