#ifndef MAINVIEWINTERFACE_H
#define MAINVIEWINTERFACE_H

#ifndef BASEVIEW_H
#include "../baseview.h"
#endif
#ifndef MAINENGINEINTERFACE_H
#include "main_engineinterface.h"
#endif

typedef std::unique_ptr<MainViewInterface> upMainViewInterface;

class MainViewInterface :
        public BaseView<MainEngineInterface>
{
//____________________________________________________Interface__
public:

    virtual void setNameUser(const QVariant& name) = 0;
    virtual void setNameLK(const QVariant& name) = 0;
    virtual void setNameCurLL(const QVariant& nameCurLL) = 0;

    virtual void messageDctAlreadyExist() = 0;

    virtual void showView() = 0;
    virtual void hideView() = 0;

//_______________________________________________Initialization__
public:
    virtual ~MainViewInterface() = default;
    virtual void setModelLL(QAbstractItemModel* model) = 0;
    virtual void setModelLanguages(QAbstractItemModel* model) = 0;
    virtual void setModelDct(QAbstractItemModel* model) = 0;
    virtual void setModelWords(QAbstractItemModel* model) = 0;

protected:
    virtual void initialize_() = 0;
//_______________________________________________________________
};

#endif // MAINVIEWINTERFACE_H
