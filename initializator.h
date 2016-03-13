#ifndef INITIALIZATOR_H
#define INITIALIZATOR_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "inclusion_for_dictionary.h"
#endif

#include "Model/types.h"
#include "View/ModulAccount/modul_account.h"
#include "View/ModulMain/modul_main.h"

class Initializator:
        public QApplication
{
//_______________________________Interface__
public:
    int initialize();

//__________________________Initialization__
public:
    Initializator(int & argc, char ** argv);
    ~Initializator() = default;

    void initialize_();
    void createTypesNodes();
    void createTypesLinks();
    void createPartsOfSpeech();
    void createLanguages();

    void givePartsOfSpeechNames();

    void createFunctional();

    void createModulAccount();
    void createModulMain();

//__________________________________Hidden__
private:
    enum PartsOfSpeech{General      ,
                       Noun         ,
                       Verb         ,
                       Adjective    ,
                       Adverb       ,
                       Pronoun      ,
                       Preposition  ,
                       Conjunction  ,
                       Interjection ,
                       Article      ,
                       Participle   ,
                       Transgressive,
                       Particle     ,
                       Numeral      };

    QMap<int, IDNode> idMapPartsOfSpeech_;

    spDataBase base_;

    upAccountEngine engineAccount_;
    upMainEngine engineMain_;

    spFunctionalAccount fAc_;
    spFunctionalAccounts fAcs_;
    spFunctionalLL fLL_;

    IDTypeNode idtnRoot_;
    IDTypeNode idtnAccounts_;
    IDTypeNode idtnAccount_;
    IDTypeNode idtnLanguages_;
    IDTypeNode idtnLanguage_;
    IDTypeNode idtnParts_OfSpeech_;
    IDTypeNode idtnPart_OfSpeech_;
    IDTypeNode idtnRefLK_;
    IDTypeNode idtnRefLL_;
    IDTypeNode idtnRefPS_;
    IDTypeNode idtnDct_;
    IDTypeNode idtnLLForDctLK_;
    IDTypeNode idtnWord_;

    IDTypeLink idtlStrong_;
    IDTypeLink idtlWeak_;
    IDTypeLink idtlRef_;

    IDNode idRoot_;
    IDNode idLanguages_;
    IDNode idAccounts_;
    IDNode idPartsOfSpeech_;

private:
    bool notify(QObject* obj, QEvent *e);
    void message(const QString& text);
//__________________________________________
};

#endif // INITIALIZATOR_H
