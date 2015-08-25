#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>

#include <iostream>
#include <fstream>

class FileReader
{
public:

    FileReader();

    ~FileReader();

    void
    openFile(const char*);

    QString
    getWord();

    std::string
    getLine();

    unsigned int
    getLineNb() const;

    bool
    endOfFile() const;

protected:

    unsigned int
    lineNb;

    std::ifstream
    font;
};

#endif // FILEREADER_H
