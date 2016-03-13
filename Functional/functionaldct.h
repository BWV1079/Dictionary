#ifndef FUNCTIONALDCT_H
#define FUNCTIONALDCT_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

struct FunctionalDctArgs
{
    spDataBase base_;
    IDTypeNode idtnWord_;
    IDTypeNode idtnLL_;
    IDTypeNode idtnLK_;
    IDTypeNode idtnPS_;
    IDTypeNode idtnRefPS_;
    IDTypeLink idtlWordDct_;
    IDTypeLink idtlWordLang_;
    IDTypeLink idtlRefPS_;
    IDTypeLink idtlRef_;
    int keyWord_;
    int keyTranscription_;
    bool check();
};

class FunctionalDct;
typedef std::shared_ptr<FunctionalDct> spFunctionalDct;

class FunctionalDct
{
public:
    explicit FunctionalDct(FunctionalDctArgs&& args);

public:
    void beg(){a.base_->beginChange();}
    void end(){a.base_->endChange();}
    spNode createWord(const spNode& dct,
                      const QString& word,
                      const QString& transcription);
    spNode getRefLang(const spNode& dct);

private:
    FunctionalDctArgs a;
};

#endif // FUNCTIONALDCT_H
