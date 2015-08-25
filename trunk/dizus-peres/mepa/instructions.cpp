#include "instructions.h"

#include "virtualmachine.h"

#include <QDebug>


void
armz::exec( VirtualMachine* _parent )
{
    QStringList
    args = _parent->getCommandAtPc()->args;

    int
    K = args[0].toInt(),
    N = args[1].toInt();

    _parent->memory_stack[ _parent->registers_stack[ K ] + N ] = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    _parent->pc++;
}

QString
armz::name = "armz";

void
dsvs::exec( VirtualMachine* _parent )
{
    QString
    arg = _parent->getCommandAtPc()->args.at(0).trimmed();

    int
    addr;

    if ( this->isLabel(arg))
    {
        addr = _parent->getLabel(arg);
    }
    else
    {
        addr = arg.toInt();
    }
    _parent->pc = _parent->program_stack.find(addr);
}

QString
dsvs::name = "dsvs";

void
dsvf::exec( VirtualMachine* _parent )
{
    if ( _parent->memory_stack.last() > 0 || _parent->memory_stack.last() < 0)
    {
        _parent->pc++;
    }
    else
    {
        QString
        arg = _parent->getCommandAtPc()->args.at(0);

        int
        addr;

        if ( this->isLabel(arg))
        {
            addr = _parent->getLabel(arg);
        }
        else
        {
            addr = arg.toInt();
        }
        _parent->pc = _parent->program_stack.find(addr);
    }
    _parent->memory_stack.pop_back();
}

QString
dsvf::name = "dsvf";

void
nada::exec( VirtualMachine* _parent )
{
    _parent->pc++;
}

QString
nada::name = "nada";

void
leit::exec( VirtualMachine* _parent )
{
    _parent->memory_stack.push_back(_parent->stdIn());

    _parent->pc++;
}

QString
leit::name = "leit";

void
impr::exec( VirtualMachine* _parent )
{
    _parent->stdOut();
    _parent->memory_stack.pop_back();
    _parent->pc++;
}

QString
impr::name = "impr";

void
impl::exec( VirtualMachine* _parent )
{
    _parent->stdOut(true);
    _parent->memory_stack.pop_back();
    _parent->pc++;
}

QString
impl::name = "impl";

void
impc::exec( VirtualMachine* _parent )
{
    _parent->stdOut(true,true);
    _parent->memory_stack.pop_back();
    _parent->pc++;
}

QString
impc::name = "impc";

void
inpp::exec( VirtualMachine* _parent )
{
    _parent->memory_stack.clear();
    _parent->pc = _parent->program_stack.begin();

    _parent->pc++;
}

QString
inpp::name = "inpp";

void
amem::exec( VirtualMachine* _parent )
{
    int
    space = _parent->getCommandAtPc()->args.at(0).toInt();

    for( int i = 0; i < space; i++)
        _parent->memory_stack.push_back(0);

    _parent->pc++;
}

QString
amem::name = "amem";

void
para::exec( VirtualMachine* _parent )
{
    _parent->stoped = true;
}

QString
para::name = "para";

void
crct::exec( VirtualMachine* _parent )
{
    _parent->memory_stack.push_back( _parent->getCommandAtPc()->args.at(1).toInt() );
    _parent->pc++;
}

QString
crct::name = "crct";

void
crvl::exec( VirtualMachine* _parent )
{
    int
    K = _parent->getCommandAtPc()->args.at(0).toInt(),
    N = _parent->getCommandAtPc()->args.at(1).toInt();

    int
    value = _parent->memory_stack.at( _parent->registers_stack.at(K) + N );

    _parent->memory_stack.push_back(value);

    _parent->pc++;
}

QString
crvl::name = "crvl";

void
soma::exec( VirtualMachine* _parent )
{
    int
    pre_last,
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    pre_last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    _parent->memory_stack.push_back(pre_last + last);

    _parent->pc++;
}

QString
soma::name = "soma";

void
subt::exec( VirtualMachine* _parent )
{
    int
    pre_last,
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    pre_last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    _parent->memory_stack.push_back(pre_last - last);

    _parent->pc++;
}

QString
subt::name = "name";

void
mult::exec( VirtualMachine* _parent )
{
    int
    pre_last,
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    pre_last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    _parent->memory_stack.push_back(pre_last * last);

    _parent->pc++;
}

QString
mult::name = "mult";

void
divi::exec( VirtualMachine* _parent )
{
    int
    pre_last,
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    pre_last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    _parent->memory_stack.push_back(pre_last / last);

    _parent->pc++;
}

QString
divi::name = "divi";

void
invr::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();

    _parent->memory_stack.pop_back();

    _parent->memory_stack.push_back(-1 * last);

    _parent->pc++;
}

QString
invr::name = "invr";

void
conj::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if(!(_parent->memory_stack.last()==1 && last==1))
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
conj::name = "conj";

void
disj::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if( _parent->memory_stack.last()==1 || last==1 )
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(1);
    }
    else
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
disj::name = "disj";

void
nega::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();

    _parent->memory_stack.pop_back();

    _parent->memory_stack.push_back(1 - last);
    _parent->pc++;
}

QString
nega::name = "nega";

void
cmme::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if ( _parent->memory_stack.last() < last )
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(1);
    }
    else
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
cmme::name = "cmme";

void
cmma::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if ( _parent->memory_stack.last() > last )
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(1);
    }
    else
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
cmma::name = "cmma";

void
cmig::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if ( _parent->memory_stack.last() == last )
    {
        _parent->memory_stack[ _parent->memory_stack.size() -1 ] = 1;
    }
    else
    {
        _parent->memory_stack[ _parent->memory_stack.size() -1 ] = 0;
    }
    _parent->pc++;
}

QString
cmig::name = "cmig";

void
cmdg::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if ( _parent->memory_stack.last() != last )
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(1);
    }
    else
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
cmdg::name = "cmdg";

void
cmeg::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if ( _parent->memory_stack.last() <= last )
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(1);
    }
    else
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
cmeg::name = "cmeg";

void
cmag::exec( VirtualMachine* _parent )
{
    int
    last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    if ( _parent->memory_stack.last() >= last )
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(1);
    }
    else
    {
        _parent->memory_stack.pop_back();
        _parent->memory_stack.push_back(0);
    }

    _parent->pc++;
}

QString
cmag::name = "cmag";

void
armi::exec( VirtualMachine* _parent)
{
    int
    K = _parent->getCommandAtPc()->args.at(0).toInt(),
    N = _parent->getCommandAtPc()->args.at(1).toInt(),
    position_memory = _parent->memory_stack[ _parent->registers_stack[K] + N ] ,
    value = _parent->memory_stack.last();

    _parent->memory_stack[position_memory] = value;
    _parent->memory_stack.pop_back();

    _parent->pc++;
}

QString
armi::name = "armi";

void
armm::exec( VirtualMachine* _parent)
{
    int
    last = _parent->memory_stack.last(),
    pre_last;

    _parent->memory_stack.pop_back();

    pre_last = _parent->memory_stack.last();
    _parent->memory_stack.pop_back();

    _parent->memory_stack[pre_last] = last;

    _parent->pc++;
}

QString
armm::name = "armm";

void
cren::exec( VirtualMachine* _parent)
{
    int
    N = _parent->getCommandAtPc()->args.at(0).toInt(),
    K = _parent->getCommandAtPc()->args.at(1).toInt(),
    value = _parent->registers_stack[K] + N;

    _parent->memory_stack.push_back( value );

    _parent->pc++;
}

QString
cren::name = "cren";

void
crma::exec( VirtualMachine* _parent)
{
    int
    pos = _parent->memory_stack.size() - 1;

    _parent->memory_stack[pos] = _parent->memory_stack[ _parent->memory_stack[pos] ];

    _parent->pc++;
}

QString
crma::name = "crma";

void
crvi::exec( VirtualMachine* _parent)
{
    int
    K = _parent->getCommandAtPc()->args.at(0).toInt(),
    N = _parent->getCommandAtPc()->args.at(1).toInt(),
    value = _parent->memory_stack[ _parent->memory_stack[_parent->registers_stack[K] + N] ];

    _parent->memory_stack.push_back(value);

    _parent->pc++;
}

QString
crvi::name = "crvi";

void
dmem::exec( VirtualMachine* _parent)
{
    int
    N = _parent->getCommandAtPc()->args.at(0).toInt();

    for ( int i = 0; i < N; i ++ )
        _parent->memory_stack.pop_back();

    _parent->pc++;
}

QString
dmem::name = "dmem";

void
enpr::exec( VirtualMachine* _parent)
{
    int
    K = _parent->getCommandAtPc()->args.at(0).toInt(),
    value = _parent->registers_stack[ K ];

    _parent->memory_stack.push_back(value);
    _parent->registers_stack[K] = _parent->memory_stack.size();

    _parent->pc++;
}

QString
enpr::name = "enpr";

void
rtpr::exec( VirtualMachine* _parent)
{
    int
    K = _parent->getCommandAtPc()->args.at(0).toInt(),
    N = _parent->getCommandAtPc()->args.at(1).toInt();

    _parent->registers_stack[K] = _parent->memory_stack.last();

    _parent->memory_stack.pop_back();
    _parent->pc = _parent->program_stack.find( _parent->memory_stack.last() );

    for ( int i = 0; i < N+1; i++)
    {
        _parent->memory_stack.pop_back();
    }


}

QString
rtpr::name = "rtpr";

void
chpr::exec( VirtualMachine* _parent)
{
    QString
    L = _parent->getCommandAtPc()->args.at(0);

    int
    value = _parent->pc.key() + 1,
    addr;

    if ( this->isLabel(L))
    {
        addr = _parent->getLabel(L);
    }
    else
    {
        addr = L.toInt();
    }
    _parent->memory_stack.push_back( value );


    _parent->pc = _parent->program_stack.find(addr);
}

QString
chpr::name = "chpr";

void
mosm::exec( VirtualMachine* _parent)
{
    std::stringstream
    dump;

    dump << "DUMP DE MEMORIA: lalala.mep" << std::endl;
    dump << "-----------------------------------" << std::endl;
    dump << "i: " << _parent->pc.key() << std::endl;
    dump << "s: " << _parent->memory_stack.size() - 1 << std::endl;

    for( int i = 0; i < _parent->registers_stack.size();  i++)
    {
        dump << "D[" << i << "]: " << _parent->registers_stack[i] << std::endl;
    }

    dump << "---------------" << std::endl;

    for( int i = 0; i < _parent->memory_stack.size();  i++)
    {
        dump << "M[" <<  i << "]: " << _parent->memory_stack[i] << std::endl;
    }

    dump << "-----------------------------------" << std::endl;

    qDebug() << dump.str().c_str();

    _parent->pc++;
}

QString
mosm::name = "mosm";


