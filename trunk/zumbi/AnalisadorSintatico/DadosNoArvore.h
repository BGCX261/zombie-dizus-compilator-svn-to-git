#ifndef DADOSNOARVORE_H
#define DADOSNOARVORE_H

#include <iostream>

class DadosNoArvore{

    public:

        DadosNoArvore(std::string, int, unsigned int, bool);

        std::string
        descricao;

        int
        levelLexico;

        unsigned int
        linha;

        bool
        isTerminal;

};

DadosNoArvore::
DadosNoArvore( std::string _descricao, int _levelLexico, unsigned int _linha, bool _isTerminal )
{
    this->descricao = _descricao;
    this->levelLexico = _levelLexico;
    this->linha = _linha;
    this->isTerminal = _isTerminal;
}

#endif // DADOSNOARVORE_H
