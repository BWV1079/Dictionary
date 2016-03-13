#ifndef ADDWORDENGINE_H
#define ADDWORDENGINE_H

#ifndef ADDWORDVIEWINTERFACE_H
#include "addword_viewinterface.h"
#endif
#ifndef ADAPTERS_DICTIONARY
#include "../../Adapters/adapters_dictionary.h"
#endif
#ifndef FUNCTIONAL
#include "../../Functional/functional.h"
#endif

class AddWordEngine;
typedef std::unique_ptr<AddWordEngine> upAddWordEngine;

class AddWordEngine :
        public AddWordEngineInterface
{
//____________________________________________Interface__
public:
    void setTranscription(const QVariant& text) override final;
    void appendTranslation(const QVariant& translation,
                           const QVariant& ps) override final;

//_______________________________________Initialization__
public:
    explicit AddWordEngine(upAddWordViewInterface&& view,
                           const spNode& dctFirst,
                           const spNode& dctSecond,
                           const spNode& word,
                           upAdapterSimple&& aAllPS,
                           const QMap<QString, spAdapterSimple>& mapPS,
                           const spFunctionalLL& fLL,
                           const spFunctionalDct& fDct);
    ~AddWordEngine() = default;

private:
    void initialize_() override final;

//_______________________________________________Hidden__
private:
    spNode dctFirst_;
    spNode dctSecond_;
    spNode word_;
    QMap<QString, spAdapterSimple> mapPS_;
    spFunctionalLL fLL_;
    spFunctionalDct fDct_;
    upAdapterSimple aAllPS_;
//_______________________________________________________
};

#endif // ADDWORDENGINE_H
