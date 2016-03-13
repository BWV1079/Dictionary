#ifndef INITIALIZATOR_H
#include "initializator.h"
#endif

void Initializator::createTypesNodes()
{
    spCreatorNode simple       (new CreatorNode());
    spCreatorNode account      (new TypeAccount());
    spCreatorNode language     (new TypeLanguage());
    spCreatorNode partOfSpeech (new TypePartOfSpeech());
    spCreatorNode dct          (new TypeDct());
    spCreatorNode llForDctLK   (new TypeLLForDctLK());
    spCreatorNode word         (new TypeWord());

    idtnRoot_           = base_->registerTypeNode(simple);
    idtnAccounts_       = base_->registerTypeNode(simple);
    idtnLanguages_      = base_->registerTypeNode(simple);
    idtnParts_OfSpeech_ = base_->registerTypeNode(simple);
    idtnRefLK_          = base_->registerTypeNode(simple);
    idtnRefLL_          = base_->registerTypeNode(simple);
    idtnRefPS_          = base_->registerTypeNode(simple);

    idtnAccount_        = base_->registerTypeNode(account);
    idtnLanguage_       = base_->registerTypeNode(language);
    idtnPart_OfSpeech_  = base_->registerTypeNode(partOfSpeech);
    idtnDct_            = base_->registerTypeNode(dct);
    idtnLLForDctLK_     = base_->registerTypeNode(llForDctLK);
    idtnWord_           = base_->registerTypeNode(word);
}

void Initializator::createTypesLinks()
{
    spCreatorLink creator(new CreatorLink());
    idtlStrong_ = base_->registerTypeLink(creator, true);
    idtlWeak_   = base_->registerTypeLink(creator, false);
    idtlRef_    = base_->registerTypeLink(creator, false);
}

void Initializator::createPartsOfSpeech()
{
    idPartsOfSpeech_ = base_->createNode(idRoot_, idtnParts_OfSpeech_, idtlStrong_);

    auto lambda = [&](int n){
        idMapPartsOfSpeech_.insert(n, base_->createNode(idPartsOfSpeech_,
                                                        idtnPart_OfSpeech_,
                                                        idtlStrong_));
    };

    lambda(General      );
    lambda(Noun         );
    lambda(Verb         );
    lambda(Adjective    );
    lambda(Adverb       );
    lambda(Pronoun      );
    lambda(Preposition  );
    lambda(Conjunction  );
    lambda(Interjection );
    lambda(Article      );
    lambda(Participle   );
    lambda(Transgressive);
    lambda(Particle     );
    lambda(Numeral      );

    givePartsOfSpeechNames();
}

void Initializator::givePartsOfSpeechNames()
{
    auto lambda = [&](int n, const QString& name){
        base_->getNode(idMapPartsOfSpeech_[n])->setData(TypePartOfSpeech::Name, name);
    };

    lambda(General      , QObject::tr("General"      ));
    lambda(Noun         , QObject::tr("Noun"         ));
    lambda(Verb         , QObject::tr("Verb"         ));
    lambda(Adjective    , QObject::tr("Adjective"    ));
    lambda(Adverb       , QObject::tr("Adverb"       ));
    lambda(Pronoun      , QObject::tr("Pronoun"      ));
    lambda(Preposition  , QObject::tr("Preposition"  ));
    lambda(Conjunction  , QObject::tr("Conjunction"  ));
    lambda(Interjection , QObject::tr("Interjection" ));
    lambda(Article      , QObject::tr("Article"      ));
    lambda(Participle   , QObject::tr("Participle"   ));
    lambda(Transgressive, QObject::tr("Transgressive"));
    lambda(Particle     , QObject::tr("Particle"     ));
    lambda(Numeral      , QObject::tr("Numeral"      ));
}

void Initializator::createLanguages()
{
    idLanguages_ = base_->createNode(idRoot_, idtnLanguages_, idtlStrong_);
    auto createLang = [&](const QVariant& nameEng,
                          const QVariant& nameShort,
                          const QVariant& nameVernacular,
                          const QVariant& transcriptionSigns)
    {
        auto id = base_->createNode(idLanguages_, idtnLanguage_, idtlStrong_);
        auto n = base_->getNode(id);
        n->setData(TypeLanguage::NameEng,            nameEng);
        n->setData(TypeLanguage::NameShort,          nameShort);
        n->setData(TypeLanguage::NameVernacular,     nameVernacular);
        n->setData(TypeLanguage::TranscriptionSigns, transcriptionSigns);
        return id;
    };

    auto idEn = createLang("English", "en", "English", "");
    auto idRu = createLang("Russian", "ru", "Русский", "");

    createLang("French"    , "", "", "");  //           /
    createLang("German"    , "", "", "");  //           /
    createLang("Spanish"   , "", "", "");  //           /
    createLang("Japanese"  , "", "", "");  //           /
    createLang("Mandarin"  , "", "", "");  //           /
    createLang("Hindi"     , "", "", "");  //           /
    createLang("Arabic"    , "", "", "");  //           /
    createLang("Portuguese", "", "", "");  //           /
    createLang("Bengali"   , "", "", "");  // Бутафория /
    createLang("Punjabi"   , "", "", "");  //           /
    createLang("Wu"        , "", "", "");  //           /
    createLang("Malay"     , "", "", "");  //           /
    createLang("Javanese"  , "", "", "");  //           /
    createLang("Telugu"    , "", "", "");  //           /
    createLang("Vietnamese", "", "", "");  //           /
    createLang("Korean"    , "", "", "");  //           /
    createLang("Marathi"   , "", "", "");  //           /
    createLang("Tamil"     , "", "", "");  //           /

    auto connectLang = [&](const IDNode& id1, const IDNode id2){
        base_->connectNodes(id1, id2, idtlWeak_);
    };

    connectLang(idEn, idMapPartsOfSpeech_[General      ]);
    connectLang(idEn, idMapPartsOfSpeech_[Noun         ]);
    connectLang(idEn, idMapPartsOfSpeech_[Verb         ]);
    connectLang(idEn, idMapPartsOfSpeech_[Adjective    ]);
    connectLang(idEn, idMapPartsOfSpeech_[Adverb       ]);
    connectLang(idEn, idMapPartsOfSpeech_[Pronoun      ]);
    connectLang(idEn, idMapPartsOfSpeech_[Preposition  ]);
    connectLang(idEn, idMapPartsOfSpeech_[Conjunction  ]);
    connectLang(idEn, idMapPartsOfSpeech_[Interjection ]);
    connectLang(idEn, idMapPartsOfSpeech_[Article      ]);

    connectLang(idRu, idMapPartsOfSpeech_[General      ]);
    connectLang(idRu, idMapPartsOfSpeech_[Noun         ]);
    connectLang(idRu, idMapPartsOfSpeech_[Verb         ]);
    connectLang(idRu, idMapPartsOfSpeech_[Adjective    ]);
    connectLang(idRu, idMapPartsOfSpeech_[Adverb       ]);
    connectLang(idRu, idMapPartsOfSpeech_[Pronoun      ]);
    connectLang(idRu, idMapPartsOfSpeech_[Preposition  ]);
    connectLang(idRu, idMapPartsOfSpeech_[Conjunction  ]);
    connectLang(idRu, idMapPartsOfSpeech_[Interjection ]);
    connectLang(idRu, idMapPartsOfSpeech_[Participle   ]);
    connectLang(idRu, idMapPartsOfSpeech_[Transgressive]);
    connectLang(idRu, idMapPartsOfSpeech_[Particle     ]);
    connectLang(idRu, idMapPartsOfSpeech_[Numeral      ]);
}

void Initializator::createFunctional()
{
    fAcs_ = spFunctionalAccounts(new FunctionalAccounts(base_,
                                                        idAccounts_,
                                                        idtnAccount_,
                                                        idtlStrong_,
                                                        TypeAccount::NameUser));
    fAc_ = spFunctionalAccount(new FunctionalAccount(base_,
                                                     idLanguages_,
                                                     idtnRefLK_,
                                                     idtnRefLL_,
                                                     idtnLanguage_,
                                                     idtnLLForDctLK_,
                                                     idtlStrong_,
                                                     idtlStrong_,
                                                     idtlRef_,
                                                     TypeAccount::NameUser,
                                                     TypeLanguage::NameEng,
                                                     TypeLLForDctLK::Name,
                                                     TypeAccount::NameCurLL));
    FunctionalLLArgs aLL;
    aLL.base_              = base_;
    aLL.idtnDct_           = idtnDct_;
    aLL.idtnLLForDctLK_    = idtnLLForDctLK_;
    aLL.idtlDct_           = idtlStrong_;
    aLL.idtlLLForDctLK_    = idtlStrong_;
    aLL.idtlDctLK_         = idtlWeak_;
    aLL.idtlRef_           = idtlRef_;
    aLL.keyNameDct_        = TypeDct::Name;
    aLL.keyNameLang_       = TypeLanguage::NameEng;
    aLL.keyNameLLForDctLK_ = TypeLLForDctLK::Name;

    fLL_ = spFunctionalLL(new FunctionalLL(std::move(aLL)));
}

void Initializator::createModulAccount()
{
    upAdapterSimple aAccounts(new AdapterSimple(base_, idtnAccount_, TypeAccount::NameUser));
    aAccounts->setNode(base_->getNode(idAccounts_));
    upAdapterSimple aLK(new AdapterSimple(base_, idtnLanguage_, TypeLanguage::NameEng));
    aLK->setNode(base_->getNode(idLanguages_));
    upAdapterHideRow aLL(new AdapterHideRow(base_, idtnLanguage_, TypeLanguage::NameEng));
    aLL->setNode(base_->getNode(idLanguages_));

    upAccountViewInterface view(new AccountView());
    engineAccount_.reset(new AccountEngine(std::move(view),
                                           std::move(aAccounts),
                                           std::move(aLK),
                                           std::move(aLL),
                                           fAc_, fAcs_,
                                           [this](const spNode& node){
                                                this->engineMain_->setAccount(node);
                                                this->engineMain_->show();
                                                this->engineAccount_->hide();
                                           }));
    engineAccount_->initialize();
    engineAccount_->show();
}

void Initializator::createModulMain()
{
    upAdapterSimpleRef adapterLL(new AdapterSimpleRef(base_, idtnRefLL_, TypeLanguage::NameEng, idtlRef_));
    upAdapterHideRows adapterLang(new AdapterHideRows(base_, idtnLanguage_, TypeLanguage::NameEng, QList<QVariant>()));
    upAdapterSimple adapterDct(new AdapterSimple(base_, idtnDct_, TypeDct::Name));
    upAdapterWords adapterWords(new AdapterWords(base_,
                                                 idtnWord_,
                                                 idtnRefLL_,
                                                 idtnRefLK_,
                                                 idtlRef_,
                                                 TypeLanguage::NameEng,
                                                 TypeWord::Name,
                                                 TypeWord::Transcription));
    adapterLang->setNode(base_->getNode(idLanguages_));

    upMainViewInterface view(new MainView());
    engineMain_.reset(new MainEngine(std::move(view),
                                     fAcs_, fAc_, fLL_,
                                     std::move(adapterLL),
                                     std::move(adapterLang),
                                     std::move(adapterDct),
                                     std::move(adapterWords)));
    engineMain_->initialize();
}
