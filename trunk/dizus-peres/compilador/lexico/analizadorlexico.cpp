#include "analizadorlexico.h"
#include "enumTypes.h"
#include <cstdlib>
AnalizadorLexico::AnalizadorLexico()
{
    inicializarEstados();
    setRules();
    this->st=this->start;
}
AnalizadorLexico::~AnalizadorLexico(){
    this->destroiEstados();
}
void AnalizadorLexico::inicializarEstados()
{
    //estados não finais
    this->start = new State("start");
    this->commentBlock1 = new State("commentBlock1");
    this->commentBlock2 = new State("commentBlock2");
    this->inComment = new State("inComment");
    this->lineComment = new State("lineComment");
    //fim Estados não Finais;

    //estados Finais
    this->intError = new State("intError",true, Types::ERR);
    this->idError = new State("idError",true, Types::ERR);
    this->inOpr1 = new State("inOpr1",true,Types::OPR);
    this->inOpr2 = new State("inOpr2", true,Types::OPR);
    this->inOpr3 = new State("inOpr3",true,Types::OPR);
    this->cmt = new State("cmt",true,Types::CMT);
    this->opr = new State("opr",true,Types::OPR);
    this->idt = new State("idt",true,Types::IDT);
    this->integer = new State("int",true,Types::INT);
    //fim Estados não Finais;
}
void AnalizadorLexico::destroiEstados(){
    //estados não finais
    delete this->start;
    delete this->inOpr1;
    delete this->inOpr2;
    delete this->inOpr3;
    delete this->commentBlock1;
    delete this->commentBlock2;
    delete this->inComment;
    delete this->lineComment;
    delete this->intError;
    delete this->idError;
    //fim Estados não Finais;

    //estados Finais
    delete this->cmt;
    delete this->opr;
    delete this->idt;
    delete this->integer;
    //fim Estados não Finais;
}
void AnalizadorLexico::setRules(){
    this->start->addRule(" \a\n\t",this->start);
    this->start->addRule("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",this->idt);
    this->start->addRule("+-*/,;=!()[]%", this->opr);
    this->start->addRule("<",this->inOpr2);
    this->start->addRule(">:",this->inOpr1);
    this->start->addRule(".",this->inOpr3);
    this->start->addRule("|",this->inComment);
    this->start->addRule("1234567890",this->integer);

    this->idt->addRule("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_",this->idt);
    this->idt->addRule("\"#$&'?@^~´`",this->idError);
    this->idError->addRule("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890",this->idError);

    this->inOpr1->addRule("=", this->opr);
    this->inOpr2->addRule(">=", this->opr);
    this->inOpr3->addRule(".", this->opr);

    this->inComment->addRule("*",this->commentBlock1);
    this->inComment->addRule("|",this->lineComment);
    this->commentBlock1->addRule("*",this->commentBlock2);
    this->commentBlock1->addRule("*",this->commentBlock1,true);
    this->commentBlock2->addRule("|",this->cmt);
    this->commentBlock2->addRule("|",this->commentBlock1,true);
    this->commentBlock2->addRule("*",this->commentBlock2);
    this->lineComment->addRule("\n", this->cmt);
    this->lineComment->addRule("\n", this->lineComment,true);

    this->integer->addRule("1234567890",this->integer);
    this->integer->addRule("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",this->intError);
    this->intError->addRule("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890",this->intError);
}
void AnalizadorLexico::Processa(std::string &in, std::string &out){
    int cont=0;
    std::string buffer;
    State * aux = 0;
//    std::string v[6] = {"TO_IN",
//                         "TO_ID",
//                         "TO_OP",
//                         "TO_CM",
//                         "TO_ER",
//                         "TO_PR"};
    for(unsigned int i=0;i<=in.size();i++){
        in[i] = tolower(in[i]);
        aux = st->Process(in[i]);
        if((aux==0) && st->getIsFinal()){
	    int num = 0;
            int auxtk = st->getToken();
            switch(auxtk){
                case Types::INT:
                    num = ( atoi(buffer.c_str()));
                    if(num>65535){
                        out+=" [TO_ER,7] ";
                    }
                    else{
                        out+=" [TO_IN,"+buffer+"] ";
                    }
                break;
                case Types::IDT:
                    if(this->PalavraReservada(buffer))
                    {
                        out+=" [TO_PR,PA_"+StrUperCase(buffer)+"] ";
                    }
                    else{
                        out+=" [TO_ID,'"+buffer+"']";
                    }
                break;
                case Types::OPR:
                    if(in[i-1]=='*'&&in[i]=='|'){
                        out+=" [TO_ER,3] ";
                    }
                    else
                        out+=" [TO_OP,"+this->isOperador(buffer)+"] ";
                break;
                case Types::CMT:

                break;
                case Types::ERR:
                    if(st->getNome()=="intError")
                        out+=" [TO_ER,6] ";
                    if(st->getNome()=="idError")
                        out+=" [TO_ER,5] ";
                default:
                break;
            }
        }
        buffer+=in[i];
        if((aux==0)&& !st->getIsFinal()){
            if(st->getNome()=="start"){
                if(buffer.size()!=0 && buffer[0]!='\0'){
                   out+=" [TO_ER,4] ";
                   std::cout<<in[i]<<std::endl;
                   buffer.clear();
                   i--;
               }
            }else if(st->getNome()=="inComment"){
                out+=" [TO_ER,4] ";
            }
        }
       // buffer+=in[i];
        if(aux==this->start){
            buffer.clear();
        }
        if(aux==0){
            st = this->start;
            if(cont==0){
                buffer.clear();
                i--;
            }
            cont++;
        }
        else{
            cont=0;
            st = aux;
        }
    }
}


bool AnalizadorLexico::PalavraReservada(std::string param){
    if(param=="program")return true;
    if(param=="target")return true;
    if(param=="const")return true;
    if(param=="is")return true;
    if(param=="typedef")return true;
    if(param=="array")return true;
    if(param=="record")return true;
    if(param=="end")return true;
    if(param=="var")return true;
    if(param=="proc")return true;
    if(param=="func")return true;
    if(param=="begin")return true;
    if(param=="goto")return true;
    if(param=="if")return true;
    if(param=="then")return true;
    if(param=="else")return true;
    if(param=="forall")return true;
    if(param=="in")return true;
    if(param=="do")return true;
    if(param=="while")return true;
    if(param=="and")return true;
    if(param=="or")return true;
    if(param=="not")return true;
    if(param=="int")return true;
    if(param=="id")return true;
    if(param=="to")return true;
    if(param=="downto")return true;
    if(param=="procedure")return true;
    if(param=="function")return true;
//    if(param=="read")return true;
//    if(param=="write")return true;
    if(param=="of")return true;
    if(param=="div")return true;
    return false;
}
std::string AnalizadorLexico::isOperador(std::string str)
{
    std::string ret;
    if(str=="<>") ret = "OP_DIFERE";
    if(str=="+") ret = "OP_MAIS";
    if(str=="-") ret = "OP_MENOS";
    if(str=="*") ret = "OP_VEZES";
    if(str=="/") ret = "OP_DIV";
    if(str==".") ret = "OP_PTO";
    if(str==",") ret = "OP_VIRG";
    if(str==":") ret = "OP_2PTO";
    if(str==";") ret = "OP_PTVG";
    if(str=="=") ret = "OP_IGUAL";
    if(str=="<") ret = "OP_MENOR";
    if(str=="<=") ret = "OP_MENORIG";
    if(str==">") ret = "OP_MAIOR";
    if(str==">=") ret = "OP_MAIORIG";
    if(str==":=") ret = "OP_ATRIB";
    if(str=="..") ret = "OP_PTOPTO";
    if(str=="!") ret = "OP_EXCL";
    if(str=="(") ret = "OP_ABR_PAR";
    if(str==")") ret = "OP_FCH_PAR";
    if(str=="%") ret = "OP_RESTO";
    if(str=="[") ret = "OP_ABR_COLC";
    if(str=="]") ret = "OP_FCH_COLC";
    return ret;
}
std::string StrUperCase(std::string s){
    std::string ret;
    for(unsigned int i=0;i<s.size();i++){
        ret.push_back(toupper(s[i]));
    }
    return ret;
}
