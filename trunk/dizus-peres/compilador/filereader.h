#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <QFile>

class FileReader
{
public:

    FileReader();

    ~FileReader();

    void
    openFile(const char*);

    QString
    getLine();

    unsigned int
    getLineNb() const;

    bool
    endOfFile() const;

private:

    unsigned int
    lineNb;

    QFile
    file_src;
};

#endif // FILEREADER_H
