#ifndef FUNCTIONALACCOUNTS_H
#include "functionalaccounts.h"
#endif

FunctionalAccounts::FunctionalAccounts(const spDataBase &base,
                                       const IDNode idAccounts,
                                       IDTypeNode idtnAccount,
                                       IDTypeLink idtl,
                                       int keyNameUser) :
    base_(base),
    idAccounts_(idAccounts),
    idtnAccount_(idtnAccount),
    idtl_(idtl),
    keyNameUser_(keyNameUser)
{
    argument(base_);
    argument(idAccounts_.isValid());
    argument(idtnAccount_.isValid());
    argument(idtl_.isValid());
}

spNode FunctionalAccounts::createAccount(const QString& nameUser)
{
    auto id = base_->createUnique(idAccounts_, idtnAccount_, idtl_, keyNameUser_, nameUser);
    return id.isValid() ? base_->getNode(id) : spNode();
}

spNode FunctionalAccounts::findAccount(const QVariant& nameUser)
{
    return base_->findChild(idAccounts_, keyNameUser_, nameUser);
}
