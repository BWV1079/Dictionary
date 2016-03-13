#ifndef ACCOUNTENGINEINTERFACE_H
#define ACCOUNTENGINEINTERFACE_H

#ifndef BASEENGINE_H
#include "../baseengine.h"
#endif

class AccountViewInterface;

class AccountEngineInterface :
        public BaseEngine<AccountEngineInterface, AccountViewInterface>
{
//_____________________________________________________Interface__
public:
    virtual void eventRegister(const QString& nameUser,
                               const QString& nameLK,
                               const QString& nameLL) = 0;
    virtual void eventLogin(const QString& nameUser) = 0;
    virtual void eventSelectedLK(const QString& nameLang) = 0;

    virtual bool isAccountsListEmpty() const = 0;
    virtual bool isRegistered(const QString& nameUser) const = 0;

//________________________________________________Initialization__
public:
    virtual ~AccountEngineInterface() = default;

protected:
    virtual void initialize_() = 0;
//________________________________________________________________
};

#endif // ACCOUNTENGINEINTERFACE_H
