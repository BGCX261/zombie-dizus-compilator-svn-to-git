#include "filemanager.h"
#include "analizadorlexico.h"
FileManager::FileManager(std::string inFile, std::string outFile):
        in(inFile.c_str(),std::ios::in),
        out(outFile.c_str(),std::ios::trunc)
{
    this->inName = inFile;
    this->outName = outFile;
    this->erro = false;
    if(!out){
        std::cout<<"Arquivo de saida não pode ser aberto"<<std::endl;
        this->erro = true;
    }
    if(!in){
        std::cout<<"Arquivo de entrada '"<<inFile<<"' não pode ser aberto"<<std::endl;
        out<<inName<<" :  [TO_ER,1]"<<std::endl;
        this->erro = true;
    }
}
FileManager::~FileManager()
{
    if(in.is_open())
        in.close();
    if(out.is_open())
        out.close();
}
void FileManager::processa()
{
    if(erro)return;
    AnalizadorLexico a;
    std::string inStr;
    std::string outStr;
    int cont = 1;
    while(!in.eof()){
//        std::cout<<"-";
        std::getline(in,inStr);
        inStr+="\n";
        a.Processa(inStr,outStr);
        if(outStr!="")
            out<<this->inName<<":"<<cont<<":"<<outStr<<std::endl;
        outStr.clear();
        cont++;
    }
    if(a.getCurrentState()->getNome()=="commentBlock1"||
       a.getCurrentState()->getNome()=="commentBlock2")
        {
            out<<this->inName<<":"<<cont<<":"<<" [TO_ER:2] ";
        }
}
