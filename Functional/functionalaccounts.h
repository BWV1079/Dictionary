#ifndef FUNCTIONALACCOUNTS_H
#define FUNCTIONALACCOUNTS_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

class FunctionalAccounts;
typedef std::shared_ptr<FunctionalAccounts> spFunctionalAccounts;

class FunctionalAccounts
{
public:
    FunctionalAccounts(const spDataBase& base,
                       const IDNode idAccounts,
                       IDTypeNode idtnAccount,
                       IDTypeLink idtl,
                       int keyNameUser);

public:
    spNode createAccount(const QString& nameUser);
    spNode findAccount(const QVariant& nameUser);

private:
    spDataBase base_;
    IDNode idAccounts_;
    IDTypeNode idtnAccount_;
    IDTypeLink idtl_;
    int keyNameUser_;
};

#endif // FUNCTIONALACCOUNTS_H
