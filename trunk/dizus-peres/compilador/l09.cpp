#include "l09.h"

#include <QTreeView>
#include <QFile>
#include <QTextStream>
#include <QDebug>

L09::L09(int _argc, char** _argv)
{

    this->par_descriptions.add_options()
            ("help,H","produce help message")
            ("src-dir,DF",boost::program_options::value<std::string>(), "Localizacao do arquivo fonte. Opcao obrigatoria ao nao utilizar -I ou -H" )
            ("dest-dir,DS",boost::program_options::value<std::string>(), "Localizacao das saidas do programa." )
            ("lexical-only,L", "Produz apenas o analizador lexico")
            ("compile,R", "Executa todas as fases do compilador")
            ("syntatic,SI", boost::program_options::value<std::string>(), "Executa ate o analisador sintatico")
            ("interactive,BSI","Geracao de codigo interativa")
            ("semantic,SE",boost::program_options::value<std::string>(), "Executa apenas ate a geracao da arvore semantica")
            ("ger,GL","produz arquivo arquivo.mes  (codigo MEPA, com rotulos em lugar de enderecos)")
            ("strip-comment,GC","noo coloca comentarios no codigo gerado (.mep ou .mes)")
            ("authors,I","imprime na saida padrao a identificao do compilador e da equipe.");

    boost::program_options::store(boost::program_options::parse_command_line(_argc, _argv, this->par_descriptions), this->par_map);
    boost::program_options::notify(this->par_map);

}

L09::~L09()
{

}

int
L09::operate()
{
    if (this->par_map.count("authors"))
    {
        this->print_ids();
        return 0;
    }

    if (this->par_map.count("help"))
    {
        std::cout << "Opcoes do compilador L09:" << std::endl;
        std::cout << this->par_descriptions;
        return 0;
    }

    if (! this->par_map.count("src-dir") )
    {
        std::string
        erro = "E necessario especificar alguma instrucao basica!";

        throw erro;
    }

    QString
    filename = this->par_map["src-dir"].as<std::string>().c_str();

    this->do_lexical_analise(filename);

    if (! this->par_map.count("lexical-only") )
    {
        this->do_sintatical_analise();

    }

    return 0;
}

void
L09::do_lexical_analise( QString _filename)
{
//    qDebug() << "L09::do_lexical_analise:: iniciando analise lexica.";

    FileManager
    lexico(_filename.toStdString(),"lexico_out");
    lexico.processa();

//    qDebug() << "L09::do_lexical_analise:: lexica concluida.";
}

void
L09::do_sintatical_analise()
{
//    qDebug() << "L09::do_sintatical_analise:: iniciando analise sintatica.";

    Sintatico::Analisador::getInstance()->analize();
    Sintatico::Analisador::getInstance()->imprimeHash();


    qDebug() << "L09::do_sintatical_analise:: analise sintatica concluida.";
}


void
L09::print_ids()
{
    std::cout << "Compilador L09"                                               << std::endl
              << "Ricardo Ungerer Garciar Simoes      matricula: 200505600389" << std::endl
              << "Lucas Peres da Silva                matricula: " << std::endl
              << "Massato Kanno                       matricula: 200405600266" << std::endl;
}
