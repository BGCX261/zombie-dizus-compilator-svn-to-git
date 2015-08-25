#ifndef MEPA_H
#define MEPA_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>

#include <QtGui/QApplication>
#include <QObject>

#include <cstdlib>

#include "filereader.h"
#include "mepa_gui.h"
#include "virtualmachine.h"

class Mepa : protected VirtualMachine, protected FileReader
{
    Q_OBJECT
public:
    Mepa(int, char**);

    int
    exec();

protected:

    Instruction
    readInstruction();

    QString
    readValue();

    Instruction
    peek();

    QStringList
    readCommand();

    bool
    endOfFile();

    void
    stdOut( bool _endl = false, bool _cast_to_char = false );

    int
    stdIn();

private:

    int
    argc;

    char**
    argv;

    boost::program_options::options_description
    par_descriptions;

    boost::program_options::variables_map
    par_map;

    QApplication*
    gui;

    mepa_gui*
    window;

    int
    initGui();

    void
    showAuthors();

    void
    initConfig();

    friend class mepa_gui;
};

#endif // MEPA_H
