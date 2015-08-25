#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

class VirtualMachine;

#include <basicinstruction.h>

#include <sstream>
//Instructions

class armz : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class dsvs : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class dsvf : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class nada : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class leit : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class impr : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class impl : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class impc : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class inpp : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class amem : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class para : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class crct : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class crvl : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class soma : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class subt : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class mult : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class divi : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class invr : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class conj : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class disj : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class nega : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class cmme : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class cmma : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class cmig : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class cmdg : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class cmeg : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class cmag : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent );
    static QString name;
};

class armi : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class armm : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class cren : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class crma : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class crvi : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class dmem : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class enpr : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class rtpr : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class chpr : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

class mosm : public BasicInstruction
{
public:
    void exec( VirtualMachine* _parent);
    static QString name;
};

#endif // INSTRUCTIONS_H
