#ifndef FUNCTIONALLL_H
#define FUNCTIONALLL_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

struct FunctionalLLArgs
{
    spDataBase base_;
    IDTypeNode idtnDct_;
    IDTypeNode idtnLLForDctLK_;
    IDTypeLink idtlDct_;
    IDTypeLink idtlLLForDctLK_;
    IDTypeLink idtlDctLK_;
    IDTypeLink idtlRef_;
    int keyNameDct_;
    int keyNameLang_;
    int keyNameLLForDctLK_;
    bool check();
};

class FunctionalLL;
typedef std::shared_ptr<FunctionalLL> spFunctionalLL;

class FunctionalLL
{
public:
    FunctionalLL(FunctionalLLArgs&& args);

public:
    spNode createDct(const spNode& ll,
                     const spNode& lk,
                     const QVariant& nameDct);

private:
    FunctionalLLArgs a_;
};

#endif // FUNCTIONALLL_H
