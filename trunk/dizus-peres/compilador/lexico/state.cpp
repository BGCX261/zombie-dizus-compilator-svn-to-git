#include "state.h"
/* Classe State
 * Classe que abstrai o estado de um automato
 */

// Construtor------------------------------------------------------------
// Paramentros:
// _nome    - Nome do Estado
// _isFinal - Se o estado
State::State(std::string _nome, bool _isFinal, int _token)
{
    this->token = _token;
    this->nome = _nome;
    this->isFinal = _isFinal;
}
//------------------------------------------------------------------------
State::~State(){
    for (unsigned int i=0;i<vet.size();i++){
        delete vet[i];
    }
}
//------------------------------------------------------------------------
void State::addRule(Rule *_newRule){
    this->vet.push_back(_newRule);
}
//------------------------------------------------------------------------
void State::addRule(std::string _fromChar,State * _toState, bool _invert){
    this->addRule(new Rule(_fromChar,_toState, _invert));
}
//------------------------------------------------------------------------
State * State::Process(const char _ch){
    unsigned int pos = std::string::npos;
    for(unsigned int i=0; i<this->vet.size();i++){
//        if(_ch=='\0'&&vet[i]->hasLambida){
//            return vet[i]->toState;
//        }
        pos = this->vet[i]->getFromChar().find(_ch);
        if(pos!=std::string::npos && !(this->vet[i]->invert)){
            return this->vet[i]->toState;
        }
        if(pos==std::string::npos && this->vet[i]->invert){
            return this->vet[i]->toState;
        }
    }
    return 0;
}
//-----------------------------------------------------------------------
bool State::getIsFinal(){
    return this->isFinal;
}
//-----------------------------------------------------------------------
int State::getToken(){
    return this->token;
}
//Classe Rule------------------------------------------------------------
//Classe que abstrai uma regra de um automato,
//no caso, liga um conjunto de caracteres a um estao
Rule::Rule(std::string _fromChar, State *_toState, bool _invert){
    this->fromChar = _fromChar;
    this->toState = _toState;
    this->invert = _invert;
}
//-----------------------------------------------------------------------
//void Rule::setFromChar(std::string _fromChar){
//    this->fromChar = _fromChar;
//}
//-----------------------------------------------------------------------
std::string Rule::getFromChar()const{
    return this->fromChar;
}
//-----------------------------------------------------------------------
//void Rule::setToState(State* _toState){
//    this->toState = _toState;
//}
//-----------------------------------------------------------------------
State* Rule::getToState()const{
    return this->toState;
}
//-----------------------------------------------------------------------
bool Rule::getInvert()const{
    return this->invert;
}
