#ifndef ACCOUNTENGINE_H
#define ACCOUNTENGINE_H

#ifndef ACCOUNTVIEWINTERFACE_H
#include "account_viewinterface.h"
#endif
#ifndef ADAPTERS_DICTIONARY
#include "../../Adapters/adapters_dictionary.h"
#endif
#ifndef FUNCTIONAL
#include "../../Functional/functional.h"
#endif

class AccountEngine;
typedef std::unique_ptr<AccountEngine> upAccountEngine;

class AccountEngine :
        public AccountEngineInterface
{
//____________________________________________Interface__
public:
    void eventRegister(const QString& nameUser,
                       const QString& nameLK,
                       const QString& nameLL) override final;
    void eventLogin(const QString& nameUser) override final;
    void eventSelectedLK(const QString& nameUser) override final;

    bool isAccountsListEmpty() const override final;
    bool isRegistered(const QString& nameUser) const override final;

//_______________________________________Initialization__
public:
    explicit AccountEngine(upAccountViewInterface&& view,
                           upAdapterSimple&& aAccounts,
                           upAdapterSimple&& aLK,
                           upAdapterHideRow&& aLL,
                           const spFunctionalAccount& fAc,
                           const spFunctionalAccounts& fAcs,
                           std::function<void(const spNode& account)> showMain);
    ~AccountEngine() = default;

private:
    void initialize_() override final;

//_______________________________________________Hidden__
private:
    upAdapterSimple aAccounts_;
    upAdapterSimple aLK_;
    upAdapterHideRow aLL_;
    spFunctionalAccount fAc_;
    spFunctionalAccounts fAcs_;
    std::function<void(const spNode& account)> showMain_;
//_______________________________________________________
};

#endif // ACCOUNTENGINE_H
