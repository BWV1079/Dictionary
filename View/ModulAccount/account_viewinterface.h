#ifndef ACCOUNTVIEWINTERFACE_H
#define ACCOUNTVIEWINTERFACE_H

#ifndef BASEVIEW_H
#include "../baseview.h"
#endif
#ifndef ACCOUNTENGINEINTERFACE_H
#include "account_engineinterface.h"
#endif

typedef std::unique_ptr<AccountViewInterface> upAccountViewInterface;

class AccountViewInterface :
        public BaseView<AccountEngineInterface>
{
//____________________________________________________Interface__
public:
    virtual void messageNameUserEmpty() = 0;
    virtual void messageNameUserExist() = 0;
    virtual void messageNameUserNotFound() = 0;

    virtual void showView() = 0;
    virtual void hideView() = 0;

//_______________________________________________Initialization__
public:
    virtual ~AccountViewInterface() = default;

    virtual void setListLK(QAbstractItemModel* model) = 0;
    virtual void setListLL(QAbstractItemModel* model) = 0;

protected:
    virtual void initialize_() = 0;
//_______________________________________________________________
};

#endif // ACCOUNTVIEWINTERFACE_H
