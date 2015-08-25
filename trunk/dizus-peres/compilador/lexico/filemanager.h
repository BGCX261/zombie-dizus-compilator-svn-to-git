#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<string>
#include<fstream>
#include<iostream>
class FileManager
{
private:
    std::ifstream in;
    std::ofstream out;
    std::string inName;
    std::string outName;
    bool erro;
public:
    FileManager(std::string inFile, std::string outFile);
    ~FileManager();
    void processa();

};

#endif // FILEMANAGER_H
