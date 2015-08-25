#include <QApplication>

#include "../lexico/tipo.h"

int main ( int argc, char* argv[] )
{
    QApplication
    app( argc, argv);

    QHash<Lexic::automata_out, Lexic::automata_out>
    teste;

    Lexic::automata_out
    teste_boga;

    teste_boga.value = "myass";

    teste[ teste_boga ] = teste_boga;

    return app.exec();
}
