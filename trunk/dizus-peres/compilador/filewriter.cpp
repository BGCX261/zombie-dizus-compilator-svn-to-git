#include "filewriter.h"

FileWriter::FileWriter()
{

}

FileWriter::~FileWriter()
{
    if(this->out_file.is_open())
    {
        this->closeFile();
    }
}

void
FileWriter::WriteNewFile(std::string _file_name)
{

    if (this->out_file.is_open() )
    {
        this->closeFile();
    }

    this->out_file.open(_file_name.c_str(),std::ios::out);

    if (! this->out_file.good())
    {
        std::string
        erro = "Erro Ao abrir arquivo de saida";

        throw erro;
    }

}

void
FileWriter::closeFile()
{

}
