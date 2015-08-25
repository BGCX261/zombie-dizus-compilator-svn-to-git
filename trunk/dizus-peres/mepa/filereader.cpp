#include "filereader.h"

#include <QDebug>

FileReader::FileReader()
{
    this->lineNb = 0;
}

FileReader::~FileReader()
{
    this->font.close();
}

void
FileReader::openFile(const char* _filename)
{
    this->font.open(_filename,std::ios::in);

    if(! this->font.good())
    {
        std::string
        erro = "Erro ao abrir arquivo";

        throw erro;
    }
}

QString
FileReader::getWord()
{
    std::string
    ret;

    this->font >> ret;

    if ( this->font.peek() == '\n' )
    {
        ++this->lineNb;
    }

    return QString(ret.c_str());
}

std::string
FileReader::getLine()
{
    char
    line[256];

    std::string
    ret;

    this->font.getline(line,256,'\n');
    ret = line;

    if( this->font.fail() )
    {
        //TODO: THROW EXCEPTION.
    }

    this->lineNb++;

    return ret;
}

unsigned int
FileReader::getLineNb() const
{
    return this->lineNb;
}

bool
FileReader::endOfFile() const
{
    if ( this->font.good() )
    {
        return false;
    }

    return true;
}
