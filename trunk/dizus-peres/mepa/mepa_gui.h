#ifndef MEPA_GUI_H
#define MEPA_GUI_H

#include "ui_mepa_gui.h"

#include <QListWidgetItem>
#include <QSemaphore>
#include <QDialog>
#include <QInputDialog>

class Mepa;

class mepa_gui : public QDialog, public Ui::MepaGuiUi
{
    Q_OBJECT
public:
    mepa_gui( Mepa* _parent );

    void
    out( int _to_out );

public slots:

    void
    instructionExecuted();

    void
    progLoaded();

    void
    reloadAll();

    void
    setupUi(QDialog* _window);

private:

    Mepa*
    parent;

    void
    populateProgram();

    void
    populateMemory();

    void
    populateRegisters();

    static std::string
    translateInst( int );

};

#endif // MEPA_GUI_H
