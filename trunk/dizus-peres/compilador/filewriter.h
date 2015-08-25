#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <string>

class FileWriter
{
public:
    FileWriter();

    ~FileWriter();

    void
    WriteNewFile(std::string);

    void
    closeFile();

protected:

    std::ofstream
    out_file;
};

#endif // FILEWRITER_H
