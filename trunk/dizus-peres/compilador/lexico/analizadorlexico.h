#ifndef ANALIZADORLEXICO_H
#define ANALIZADORLEXICO_H
#include "state.h"
#include <iostream>
#include <string>
class AnalizadorLexico
{
public:
    AnalizadorLexico();
    void Processa(std::string &in,std::string &out);
    ~AnalizadorLexico();
    State * getCurrentState()const{return st;}
private:
    State * st;
    bool PalavraReservada(std::string _p);
    std::string isOperador(std::string _P);
    void inicializarEstados();
    void destroiEstados();
    void setRules();
    //estados não finais:
    State * start;
    State * inOpr1;
    State * inOpr2;
    State * inOpr3;
    State * commentBlock1;
    State * commentBlock2;
    State * inComment;
    State * lineComment;
    //fim estados não finais
    //estados finais:
    State * intError;
    State * idError;
    State * cmt;
    State * opr;
    State * idt;
    State * integer;
    //fim estados finais
};
std::string StrUperCase(std::string s);
#endif // ANALIZADORLEXICO_H
