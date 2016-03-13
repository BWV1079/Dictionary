#ifndef ACCOUNTENGINE_H
#include "account_engine.h"
#endif

//____________________________________________Interface__


void AccountEngine::eventRegister(const QString& nameUser,
                                  const QString& nameLK,
                                  const QString& nameLL)
{
    logic(isInitialized_);

    //------------------------------------------------------------------
    if(nameLK.isEmpty()){ qDebug() << "Select Lang Known"; return; }
    if(nameLL.isEmpty()){ qDebug() << "Select Lang Learn"; return; }
    //------------------------------------------------------------------

    if(nameUser.isEmpty()) { view_->messageNameUserEmpty(); return; }
    logic((nameLK != nameLL));

    auto na = fAcs_->createAccount(nameUser);
    if(!na){ view_->messageNameUserExist(); return; }

    fAc_->addLK(na, nameLK);
    fAc_->addLL(na, nameLL);

    qDebug() << "Registered " << nameUser;
    showMain_(na);
}

void AccountEngine::eventLogin(const QString& nameUser)
{
    logic(isInitialized_);
    if(nameUser.isEmpty()){ view_->messageNameUserEmpty(); return; }

    auto n = fAcs_->findAccount(nameUser);
    if(!n){ view_->messageNameUserNotFound(); return; }

    qDebug() << "Login " << nameUser;
    showMain_(n);
}

void AccountEngine::eventSelectedLK(const QString& nameUser)
{
    logic(isInitialized_);
    aLL_->hideRow(nameUser);
}

bool AccountEngine::isAccountsListEmpty() const
{
    logic(isInitialized_);
    return !(aAccounts_->rowCount(QModelIndex()));
}

bool AccountEngine::isRegistered(const QString& nameUser) const
{
    logic(isInitialized_);
    return (bool)fAcs_->findAccount(nameUser);
}

//_______________________________________Initialization__

AccountEngine::AccountEngine(upAccountViewInterface&& view,
                             upAdapterSimple&& aAccounts,
                             upAdapterSimple&& aLK,
                             upAdapterHideRow&& aLL,
                             const spFunctionalAccount& fAc,
                             const spFunctionalAccounts& fAcs,
                             std::function<void(const spNode &)> showMain) :
    aAccounts_(std::move(aAccounts)),
    aLK_(std::move(aLK)),
    aLL_(std::move(aLL)),
    fAc_(fAc),
    fAcs_(fAcs),
    showMain_(showMain)
{
    argument(view);
    argument(aAccounts_);
    argument(aLK_);
    argument(aLL_);
    setView(std::move(view));
    view_->setListLK(aLK_.get());
    view_->setListLL(aLL_.get());
}

void AccountEngine::initialize_(){}
