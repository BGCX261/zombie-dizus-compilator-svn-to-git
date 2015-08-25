#ifndef BASICINSTRUCTION_H
#define BASICINSTRUCTION_H

#include <QString>

enum Instruction {
    ARMZ = 0, //ARMAZENA VALOR
    DSVS = 1, //DESVIO INCONDICIONAL
    DSVF = 2, //DESVIO SE FALSO
    NADA = 3, //O NOME DIZ TUDO
    LEIT = 4, //LEITURA DO TECLADO
    IMPR = 5, //IMPRIME NA SAIDA PADRAO
    IMPL = 6, //IMPRIME E PULA UMA LINHA
    IMPC = 7, //IMPRIME UM CARACTERE
    INPP = 8, //INICIAR PROGRAMA PRINCIPAL
    AMEM = 9, //ALOCAR MEMÓRIA
    PARA = 10, //PARA A EXECUÇÃO
    CRCT = 11, //CARREGAR CONSTANTE
    CRVL = 12, //CARREGA VALOR
    SOMA = 13, //SOMA AO ACUMULADOR
    SUBT = 14, //SUBTRAI DO ACUMULADOR
    MULT = 15, //MULTIPLICA O ACUMULADOR
    DIVI = 16, //DIVISAO INTEIRA
    INVR = 17, //INVERTER SINAL
    CONJ = 18, //CONJUNÇÃO
    DISJ = 19, //DISJUNÇÃO
    NEGA = 20, //NEGAÇÃO
    CMME = 21, //COMPARAR MENOR
    CMMA = 22, //COMPARAR MAIOR
    CMIG = 23, //COMPARAR IGUAL
    CMDG = 24, //COMPARAR DESIGUAL
    CMEG = 25, //COMPARAR MENOR OU IGUAL
    CMAG = 26, //COMPARAR MAIOR OU IGUAL
    ARMI = 27, //ARMAZENA VALOR INDIRETO
    ARMM = 28, //ARMAZENA EM MATRIZ
    CREN = 29, //CARREGA ENDEREÇO
    CRMA = 30, //CARREGA DE MATRIZ
    CRVI = 31, //CARREGA VALOR INDIRETO
    DMEM = 32, //DESALOCA MEMÓRIA
    ENPR = 33, //ENTRA NO PROCEDIMENTO
    RTPR = 34, //RETORNA
    CHPR = 35, //CHAMA PROCEDIMENTO
    MOSM = 36, //DUMP DE MEMÓRIA
    LABEL= 37  //INDICA A PRESENCA DE UM LABEL
};

class BasicInstruction
{
public:
    virtual void exec( VirtualMachine* _parent ) = 0;

    bool isLabel( const QString _string)
    {
        bool
        ok;

        _string.toInt(&ok);

        return !ok;
    }

    static QString name;
};


#endif // BASICINSTRUCTION_H