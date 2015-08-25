#ifndef L09_H
#define L09_H

#include <QFile>
#include <QList>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>

#include "filereader.h"
#include "filewriter.h"
#include "lexico/filemanager.h"
//#include "lexico/token.h"
#include "sintatico/sintatico.h"


class L09 : protected FileWriter
{
public:
    L09(int, char**);

    ~L09();

    int
    operate();

private:

    boost::program_options::options_description
    par_descriptions;

    boost::program_options::variables_map
    par_map;

    void
    do_lexical_analise(QString _filename);

    void
    do_sintatical_analise();

    void
    print_ids();

};

#endif // L09_H
