#include "filereader.h"

#include <cstdlib>

#include <QDebug>

FileReader::FileReader()
{
    this->lineNb = 0;
}

FileReader::~FileReader()
{
    this->file_src.close();
}

void
FileReader::openFile(const char* _filename)
{
    this->file_src.setFileName(_filename);

    if(! this->file_src.open(QIODevice::ReadOnly) )
    {
        qFatal("erro ao abrir arquivo");
    }
}

QString
FileReader::getLine()
{
    char
    line[1000];

    this->file_src.readLine(line,1000);

    if( this->file_src.error() != QFile::NoError)
    {
        qFatal("Erro ao ler uma linha do arquivo");
    }

    this->lineNb++;
    return line;
}

unsigned int
FileReader::getLineNb() const
{
    return this->lineNb;
}

bool
FileReader::endOfFile() const
{
    return this->file_src.atEnd();
}
