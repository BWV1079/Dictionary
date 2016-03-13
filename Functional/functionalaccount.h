#ifndef FUNCTIONALACCOUNT_H
#define FUNCTIONALACCOUNT_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

class FunctionalAccount;
typedef std::shared_ptr<FunctionalAccount> spFunctionalAccount;

class FunctionalAccount
{
public:
    FunctionalAccount(const spDataBase& base,
                      const IDNode& idLanguages,
                      const IDTypeNode& idtnLK,
                      const IDTypeNode& idtnLL,
                      const IDTypeNode& idtnLanguage,
                      const IDTypeNode& idtnLLForDctLK,
                      const IDTypeLink& idtlLL,
                      const IDTypeLink& idtlLLForDctLK,
                      const IDTypeLink& idtlRef,
                      int keyNameUser,
                      int keyNameLang,
                      int keyNameLLForDctLK,
                      int keyCurLL);

public:
    void addLK(const spNode& account,
                   const QString& nameLK);
    void addLL(const spNode& account,
                   const QString& nameLL);
    void setCurLL(const spNode& account,
                  const QString& nameLL);
    spNode getCurLL(const spNode& account);
    spNode getLK(const spNode& account);
    QList<QVariant> getListNamesLL(const spNode& account);
    QVariant getNameLK(const spNode& account);
    QVariant getNameCurLL(const spNode& account);
    QVariant getNameUser(const spNode& account);

private:
    spDataBase base_;
    IDNode idLanguages_;
    IDTypeNode idtnLK_;
    IDTypeNode idtnLL_;
    IDTypeNode idtnLanguage_;
    IDTypeNode idtnLLForDctLK_;
    IDTypeLink idtlLL_;
    IDTypeLink idtlLLForDctLK_;
    IDTypeLink idtlRef_;
    int keyNameUser_;
    int keyNameLang_;
    int keyNameLLForDctLK_;
    int keyCurLL_;
};

#endif // FUNCTIONALACCOUNT_H
