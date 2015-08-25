#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
class Rule;
class State
{
public:
    //construtor,
    //_nome : Nome do estado
    //_isFinal : Marca se o estado é final ou não
    //_token : caso ouver um token relacionado ao estado
    State(std::string _nome, bool _isFinal = false, int _token = -1);
    //destrutor
    ~State();
    //Adiciona uma regra ao estado
    //_newRule : a nova regra, no caso quando construida fora da classe
    void addRule(Rule* _newRule);
    //Adiciona uma regra ao estado, a partir dos parametros
    //_fromChar : characteres de que levam ao estado _toState
    //_toState : Estado consequente dos caracteres _fromChar
    void addRule(std::string _fromChar, State * _toState,  bool invert = false);
    //Processa a entrada
    //_ch : Caractere a ser processado
    //Retorno : estado ao qual o caractere leva
    State * Process(char _ch);
    //Getter
    //Retorno : Se o Estado é final ou não
    bool getIsFinal();
    //retorna o token do estado, se houver;
    int getToken();
    //
    std::string getNome()const{return this->nome;}

private:
    int token;
    bool isFinal;
    std::string nome;
    std::vector <Rule*> vet;
};

class Rule{
    //classe friend, ajuda a deixar os acessos mais rápidos
    friend class State;
private:
    bool invert;
    std::string fromChar;
    State * toState;
    //bool hasLambida;
public:
    //construtor
    //_fromChar : Conjunto de caracteres que levam ao estado _toState
    //_toState : Estado consequente dos caracteres _fromChar
    //_invert : em caso de inversão da regra, os caracteres não levam ou estado
    //_hasLambida : em caso da regra houver lambida
    Rule( std::string _fromChar="", State * _toState=0,bool _invert = false );
    //getter, retorna o grupo de char da regra
    std::string getFromChar() const;
    //getter, retorna o estado da regra
    State* getToState()const;
    //getter, retorna se é invertido ou não
    bool getInvert()const;
};
#endif // STATE_H
