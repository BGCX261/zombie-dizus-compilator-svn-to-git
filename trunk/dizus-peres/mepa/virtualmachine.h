#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <QMap>
#include <QObject>
#include <QStack>
#include <QStringList>

#include "instructions.h"

typedef struct
{
    Instruction inst;

    QStringList args;

} Command;

class VirtualMachine : public QObject
{
    Q_OBJECT

public:

    ~VirtualMachine();

    int
    lblToInt( const QString );

public slots:

    void
    runProg();

    void
    stepProg();

signals:

    void
    initReg( char, int );

    void
    changeRegVal( char, int, int );

    void
    progLoaded();

    void
    chComm();

protected:


    QMap<int, Command*>
    program_stack;

    QList<int>
    registers_stack;

    QMap<Instruction,BasicInstruction*>
    instrucion_set;

    QMap<int, Command*>::iterator
    pc;

    QList<int>
    memory_stack;

    QMap<QString, int>
    labels;

    Instruction
    readInstruction();

    QString
    readValue();

    virtual Instruction
    peek();

    virtual QStringList
    readCommand();

    static Instruction
    strToInst( const QString& );

    void
    loadProg();

    virtual bool
    endOfFile();

    virtual int
    stdIn();

    virtual void
    stdOut( bool _endl = false, bool _cast_to_char = false );

    /**
     * @author Ricardo Dizus Ungerer
     *
     *  Método para inicializar o vetor de instruções.
     */
    void
    initInstructionSet();

private:

    bool
    stoped;

    void
    newLabel( const QString _label , int addr );

    int
    getLabel( const QString& _label );

    void
    execInstruction();

    Command*
    getCommandAtPc();

    friend class armz;
    friend class dsvs;
    friend class dsvf;
    friend class nada;
    friend class leit;
    friend class impr;
    friend class impl;
    friend class impc;
    friend class inpp;
    friend class amem;
    friend class para;
    friend class crct;
    friend class crvl;
    friend class soma;
    friend class subt;
    friend class mult;
    friend class divi;
    friend class invr;
    friend class conj;
    friend class disj;
    friend class nega;
    friend class cmme;
    friend class cmma;
    friend class cmig;
    friend class cmdg;
    friend class cmeg;
    friend class cmag;
    friend class armi;
    friend class armm;
    friend class chpr;
    friend class cren;
    friend class crma;
    friend class crvi;
    friend class enpr;
    friend class dmem;
    friend class rtpr;
    friend class mosm;
};

#endif // VIRTUALMACHINE_H
