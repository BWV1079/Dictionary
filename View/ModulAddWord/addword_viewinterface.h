#ifndef ADDWORDVIEWINTERFACE_H
#define ADDWORDVIEWINTERFACE_H

#ifndef BASEVIEW_H
#include "../baseview.h"
#endif
#ifndef ADDWORDENGINEINTERFACE_H
#include "addword_engineinterface.h"
#endif

typedef std::unique_ptr<AddWordViewInterface> upAddWordViewInterface;

class AddWordViewInterface :
        public BaseView<AddWordEngineInterface>
{
//____________________________________________________Interface__
public:


//_______________________________________________Initialization__
public:
    virtual ~AddWordViewInterface() = default;

    virtual void setListAllPS(QAbstractItemModel* model) = 0;
    virtual void setMapPS(const QMap<QString, QAbstractItemModel*>& map) = 0;

protected:
    virtual void initialize_() = 0;
//_______________________________________________________________
};

#endif // ADDWORDVIEWINTERFACE_H
