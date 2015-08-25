#include "virtualmachine.h"

#include <QDebug>

VirtualMachine::~VirtualMachine()
{

}

void
VirtualMachine::runProg()
{
    this->stoped = false;

    while(! this->stoped || this->pc == this->program_stack.end())
    {
        this->execInstruction();
    }
}

void
VirtualMachine::stepProg()
{
    this->stoped = false;
    this->execInstruction();
    emit chComm();
}

Instruction
VirtualMachine::readInstruction()
{
    return NADA;
}

QString
VirtualMachine::readValue()
{
    return 0;
}

Instruction
VirtualMachine::peek()
{
    return NADA;
}

QStringList
VirtualMachine::readCommand()
{
    return QStringList();
}

Instruction
VirtualMachine::strToInst( const QString& _to_convert)
{
    QString
    to_up_convert = _to_convert.toUpper();

    if (to_up_convert == "ARMZ" )
    {
        return ARMZ;
    }
    else if (to_up_convert == "DSVS" )
    {
        return DSVS;
    }
    else if (to_up_convert == "DSVF" )
    {
        return DSVF;
    }
    else if (to_up_convert == "NADA" )
    {
        return NADA;
    }
    else if (to_up_convert == "LEIT" )
    {
        return LEIT;
    }
    else if (to_up_convert == "IMPR" )
    {
        return IMPR;
    }
    else if (to_up_convert == "IMPL" )
    {
        return IMPL;
    }
    else if (to_up_convert == "IMPC" )
    {
        return IMPC;
    }
    else if (to_up_convert == "INPP" )
    {
        return INPP;
    }
    else if (to_up_convert == "AMEM" )
    {
        return AMEM;
    }
    else if (to_up_convert == "PARA" )
    {
        return PARA;
    }
    else if (to_up_convert == "CRCT" )
    {
        return CRCT;
    }
    else if (to_up_convert == "CRVL" )
    {
        return CRVL;
    }
    else if (to_up_convert == "SOMA" )
    {
        return SOMA;
    }
    else if (to_up_convert == "SUBT" )
    {
        return SUBT;
    }
    else if (to_up_convert == "MULT" )
    {
        return MULT;
    }
    else if (to_up_convert == "DIVI" )
    {
        return DIVI;
    }
    else if (to_up_convert == "INVR" )
    {
        return INVR;
    }
    else if (to_up_convert == "CONJ" )
    {
        return CONJ;
    }
    else if (to_up_convert == "DISJ" )
    {
        return DISJ;
    }
    else if (to_up_convert == "NEGA" )
    {
        return NEGA;
    }
    else if (to_up_convert == "CMME" )
    {
        return CMME;
    }
    else if (to_up_convert == "CMMA" )
    {
        return CMMA;
    }
    else if (to_up_convert == "CMIG" )
    {
        return CMIG;
    }
    else if (to_up_convert == "CMDG" )
    {
        return CMDG;
    }
    else if (to_up_convert == "CMEG" )
    {
        return CMEG;
    }
    else if (to_up_convert == "CMAG" )
    {
        return CMAG;
    }
    else if (to_up_convert == "ARMI" )
    {
        return ARMI;
    }
    else if (to_up_convert == "ARMM" )
    {
        return ARMM;
    }
    else if (to_up_convert == "CHPR" )
    {
        return CHPR;
    }
    else if (to_up_convert == "CREN" )
    {
        return CREN;
    }
    else if (to_up_convert == "CRMA" )
    {
        return CRMA;
    }
    else if (to_up_convert == "CRVI" )
    {
        return CRVI;
    }
    else if (to_up_convert == "DMEM" )
    {
        return DMEM;
    }
    else if (to_up_convert == "ENPR" )
    {
        return ENPR;
    }
    else if (to_up_convert == "RTPR" )
    {
        return RTPR;
    }
    else if (to_up_convert == "CMAG" )
    {
        return CMAG;
    }
    else if (to_up_convert == "MOSM" )
    {
        return MOSM;
    }
    else
    {
        return LABEL;
    }
}

void
VirtualMachine::loadProg()
{
    QStringList
    command_str = this->readCommand();

    Command*
    command;

    bool
    ok;

    int
    addr = 1;

    while( command_str.count() >= 1 )
    {
        command = new Command();

        command->inst = VirtualMachine::strToInst(command_str.at(1));

        command->args = command_str.at(2).split(",");

        command->args[0] = command->args.at(0).trimmed();
        if (command->args.size() > 1)
        {
            command->args[1] = command->args.at(1).trimmed();
        }

        command_str.at(0).toInt(&ok);

        if (! ok ) //label
        {
            this->newLabel(command_str.at(0).trimmed(), addr);
        }

        this->program_stack[ addr ] = command;

        command_str = this->readCommand();

        ++addr;
    }
    this->pc = this->program_stack.begin();

    emit progLoaded();

//    for ( QMap<int, Command*>::iterator it = this->program_stack.begin();
//          it != this->program_stack.end();
//          it++)
//    {
//        qDebug() << it.key() << " " << it.value()->args;
//    }
//
//    qDebug() << "DUMP DOS LABELS";

//    for ( QMap<QString, int>::iterator it = this->labels.begin();
//          it != this->labels.end();
//          it++)
//    {
//        qDebug() << it.key() << " " << it.value();
//    }
//
    for ( unsigned int i = 0 ; i < 10 ; i++ )
    {
        this->registers_stack.push_back(0);
    }
}

bool
VirtualMachine::endOfFile()
{
    return true;
}

int
VirtualMachine::stdIn()
{
    return 12;
}

void
VirtualMachine::stdOut(bool _endl, bool _cast_to_char)
{
}

void
VirtualMachine::initInstructionSet()
{
    this->instrucion_set[ARMZ] = new armz();
    this->instrucion_set[DSVS] = new dsvs();
    this->instrucion_set[DSVF] = new dsvf();
    this->instrucion_set[NADA] = new nada();
    this->instrucion_set[LEIT] = new leit();
    this->instrucion_set[IMPR] = new impr();
    this->instrucion_set[IMPL] = new impl();
    this->instrucion_set[IMPC] = new impc();
    this->instrucion_set[INPP] = new inpp();
    this->instrucion_set[AMEM] = new amem();
    this->instrucion_set[PARA] = new para();
    this->instrucion_set[CRCT] = new crct();
    this->instrucion_set[CRVL] = new crvl();
    this->instrucion_set[SOMA] = new soma();
    this->instrucion_set[SUBT] = new subt();
    this->instrucion_set[MULT] = new mult();
    this->instrucion_set[DIVI] = new divi();
    this->instrucion_set[INVR] = new invr();
    this->instrucion_set[CONJ] = new conj();
    this->instrucion_set[DISJ] = new disj();
    this->instrucion_set[NEGA] = new nega();
    this->instrucion_set[CMME] = new cmme();
    this->instrucion_set[CMMA] = new cmma();
    this->instrucion_set[CMIG] = new cmig();
    this->instrucion_set[CMDG] = new cmdg();
    this->instrucion_set[CMEG] = new cmeg();
    this->instrucion_set[CMAG] = new cmag();
    this->instrucion_set[ARMI] = new armi();
    this->instrucion_set[ARMM] = new armm();
    this->instrucion_set[CHPR] = new chpr();
    this->instrucion_set[CREN] = new cren();
    this->instrucion_set[CRMA] = new crma();
    this->instrucion_set[CRVI] = new crvi();
    this->instrucion_set[ENPR] = new enpr();
    this->instrucion_set[RTPR] = new rtpr();
    this->instrucion_set[DMEM] = new dmem();
    this->instrucion_set[MOSM] = new mosm();
}

void
VirtualMachine::newLabel( const QString _label, int addr )
{
    this->labels[_label] = addr;
}

int
VirtualMachine::getLabel( const QString& _label )
{
    int
    addr = this->labels[ _label ];
    return addr;
}

void
VirtualMachine::execInstruction()
{
    if (! this->stoped )
    {
        this->instrucion_set[ this->getCommandAtPc()->inst ]->exec(this);
    }
}

Command*
VirtualMachine::getCommandAtPc()
{
    return pc.value();
}
