#include "mepa.h"

#include <QDebug>

Mepa::Mepa(int _argc, char* _argv[])
{
    this->argc = _argc;
    this->argv = _argv;


    this->par_descriptions.add_options()
            ("help,H","produce help message")
            ("gui,J", "Executa em modo GUI" )
            ("registers,R", boost::program_options::value<int>(), "número de registradores de base")
            ("program-size,P", boost::program_options::value<int>(), "tamanho da memória de programa")
            ("memory-size,M", boost::program_options::value<int>(), "tamanho da memória de dados")
            ("authors,I","mostra os autores do programa")
            ("mosm,R",boost::program_options::value<std::string>(),"define o arquivo de saida do resultado do programa")
            ("input-file", boost::program_options::value<std::string>(), "arquivo a ser executado");

    boost::program_options::store(boost::program_options::parse_command_line(_argc, _argv, this->par_descriptions), this->par_map);
    boost::program_options::notify(this->par_map);

    this->exec();
}

int
Mepa::exec()
{
    if (this->par_map.count("authors") )
    {
        this->showAuthors();
        return 0;
    }

    if (this->par_map.count("help") )
    {
        std::cout << "Ajuda para a mepa??? Pediu, toma!" << std::endl;
        std::cout << this->par_descriptions;

        return 0;
    }

    if (! this->par_map.count("input-file") )
    {
        std::string
        error = "Erro! Nenhum arquivo para executar!";

        throw(error);
    }

    this->openFile(this->par_map["input-file"].as<std::string>().c_str());

    this->initConfig();

    this->loadProg();

    if (this->par_map.count("gui") )
    {
        return this->initGui();
    }
    else
    {
        this->runProg();
    }

    return 0;
}

Instruction
Mepa::readInstruction()
{
    QString
    instruction_str = this->getWord();

    return Mepa::strToInst(instruction_str);
}

QString
Mepa::readValue()
{
    return this->getWord();
}

Instruction
Mepa::peek()
{
    return VirtualMachine::strToInst( QString(this->font.peek()) );
}


QStringList
Mepa::readCommand()
{
    char
    command[35];

    QStringList
    ret;

    this->font.getline(command,30,'\n');

    std::string
    temp = command;

    if( temp.size() > 0 )
    {
        ret << temp.substr(0,5).c_str(); //endereço de memória
        ret << temp.substr(6,4).c_str(); //instrução
        ret << temp.substr(10,15).c_str(); //args
    }

    return ret;
}

bool
Mepa::endOfFile()
{
    return FileReader::endOfFile();
}

void
Mepa::stdOut( bool _endl, bool _cast_to_char )
{
    if ( this->par_map.count("gui") > 0)
    {
        if (! _cast_to_char )
            this->window->out( this->memory_stack.last() );
        else
            this->window->out( (char) this->memory_stack.last() );
    }
    else
    {
        std::cout << this->memory_stack.last();

        if (_endl)
            std::cout << std::endl;
    }
}

int
Mepa::stdIn()
{
    int
    ret;

    if ( this->par_map.count("gui") > 0)
    {

        return QInputDialog::getInt(0,
                                tr("Favor entrar com um numero"),
                                tr("Entrada do sistema:"),
                                0,
                                0,
                                50,
                                1);
    }
    else
    {
        std::cout << "Entre com um valor: ";
        std::cin >> ret;
    }

    return ret;
}

int
Mepa::initGui()
{
    this->gui = new QApplication( this->argc,this->argv );

    this->window = new mepa_gui(this);

    window->show();

    return this->gui->exec();
}

void
Mepa::showAuthors()
{
    std::cout << "Autores do trabalho:" << std::endl
              << "    Ricardo Ungerer Garcia Simões - 200505600359" << std::endl
              << "    Lucas Peres da Silva          - 200435603013" << std::endl
              << "    Massato Kanno                 - 200405600266" << std::endl;
}

void
Mepa::initConfig()
{
    unsigned int
    memory_stack,
    program_stack,
    registers_stack;

    if (this->par_map.count("registers") > 0)
    {
        registers_stack = this->par_map["registers"].as<unsigned int>();
    }
    else
    {
        registers_stack = 100;
    }

    if (this->par_map.count("program-size") > 0)
    {
        program_stack = this->par_map["program-size"].as<unsigned int>();
    }
    else
    {
        program_stack = 100;
    }

    if (this->par_map.count("memory-size") > 0)
    {
            memory_stack = this->par_map["memory-size"].as<unsigned int>();
    }
    else
    {
        memory_stack = 100;
    }

    this->initInstructionSet();
}
