#include "mepa_gui.h"

#include "mepa.h"
#include "basicinstruction.h"

#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <sstream>

mepa_gui::mepa_gui( Mepa* _parent )
{
    this->parent = _parent;
    this->setupUi(this);
    this->reloadAll();
}

void
mepa_gui::out( int _to_out )
{
    QMessageBox::information(0,
                             tr("Informacao MEPA:"),
                             QString("").number(_to_out));
}

void
mepa_gui::instructionExecuted()
{


}

void
mepa_gui::progLoaded()
{
    qDebug() << "Depreciado";
}

void
mepa_gui::reloadAll()
{
    this->lPC->clear();
    this->populateProgram();
    this->lMEM->clear();
    this->populateMemory();
    this->populateRegisters();
}

void
mepa_gui::setupUi(QDialog* _window)
{
    Ui::MepaGuiUi::setupUi(_window);

    QObject::connect(this->bRun, SIGNAL(clicked()),
                     this->parent, SLOT(runProg()));

    QObject::connect(this->bNext, SIGNAL(clicked()),
                     this->parent, SLOT(stepProg()));

    QObject::connect(this->parent, SIGNAL(progLoaded()),
                     this, SLOT(progLoaded()));

    QObject::connect(this->parent, SIGNAL(chComm()),
                     this, SLOT(reloadAll()));
}

void
mepa_gui::populateProgram()
{
    QListWidgetItem*
    item;

    int
    i = 0;

    std::stringstream
    azia;

    for(QMap<int,Command*>::iterator it = this->parent->program_stack.begin() ;
        it != this->parent->program_stack.end();
        it++, i++)
    {
        azia.str("");

        std::string
        item_str;

        item = new QListWidgetItem();
        azia << it.key() << " " << 
                mepa_gui::translateInst(it.value()->inst) << " " <<
                it.value()->args.join(",").toStdString();
        item_str = azia.str();
        azia.clear();

        item->setText( item_str.c_str() );
        this->lPC->addItem(item);

        if ( this->parent->pc.key() == it.key() )
        {
            item->setSelected(true);
        }
        else
        {
            item->setSelected(false);
        }
    }
}

void
mepa_gui::populateMemory()
{

    int
    i = 0;

    std::stringstream
    azia;

    std::string
    text;

    for( QList<int>::iterator it = this->parent->memory_stack.begin();
         it != this->parent->memory_stack.end();
         it++, i++ )
    {
        azia.str("");
        azia << i << " " << *it;
        text =  azia.str();
        azia.clear();
        this->lMEM->addItem(new QListWidgetItem(text.c_str()));
    }
}

void
mepa_gui::populateRegisters()
{
    int
    i = 0;

    std::stringstream
    azia;

    std::string
    text;

    this->lREG->clear();

    for( QList<int>::iterator it = this->parent->registers_stack.begin();
         it != this->parent->registers_stack.end();
         it++, i++ )
    {
        azia.str("");
        azia << i << " " << *it;
        text =  azia.str();
        azia.clear();
        this->lREG->addItem(new QListWidgetItem(text.c_str()));
    }
}

std::string
mepa_gui::translateInst( int inst)
{
    switch (inst)
    {
    case ARMZ:
        return "ARMZ";
        break;
    case DSVS:
        return "DSVS";
        break;
    case DSVF:
        return "DSVF";
        break;
    case NADA:
        return "NADA";
        break;
    case LEIT:
        return "LEIT";
        break;
    case IMPR:
        return "IMPR";
        break;
    case IMPL:
        return "IMPL";
        break;
    case IMPC:
        return "IMPC";
        break;
    case INPP:
        return "INPP";
        break;
    case AMEM:
        return "AMEM";
        break;
    case PARA:
        return "PARA";
        break;
    case CRCT:
        return "CRCT";
        break;
    case CRVL:
        return "CRVL";
        break;
    case SOMA:
        return "SOMA";
        break;
    case SUBT:
        return "SUBT";
        break;
    case MULT:
        return "MULT";
        break;
    case DIVI:
        return "DIVI";
        break;
    case INVR:
        return "INVR";
        break;
    case CONJ:
        return "CONJ";
        break;
    case DISJ:
        return "DISJ";
        break;
    case NEGA:
        return "NEGA";
        break;
    case CMME:
        return "CMMA";
        break;
    case CMIG:
        return "CMIG";
        break;
    case CMDG:
        return "CMDG";
        break;
    case CMEG:
        return "CMEG";
        break;
    case CMAG:
        return "CMAG";
        break;
    case ARMI:
        return "ARMI";
        break;
    case ARMM:
        return "ARMM";
        break;
    case CREN:
        return "CREN";
        break;
    case CRMA:
        return "CRMA";
        break;
    case CRVI:
        return "CRVI";
        break;
    case DMEM:
        return "DMEM";
        break;
    case ENPR:
        return "ENPR";
        break;
    case RTPR:
        return "RTPR";
        break;
    case CHPR:
        return "CHPR";
        break;
    case MOSM:
        return "MOSM";
        break;
    }
}
