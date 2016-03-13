#ifndef MAINENGINE_H
#define MAINENGINE_H

#ifndef MAINVIEWINTERFACE_H
#include "main_viewinterface.h"
#endif
#ifndef ADAPTERS_DICTIONARY
#include "../../Adapters/adapters_dictionary.h"
#endif
#ifndef FUNCTIONAL
#include "../../Functional/functional.h"
#endif

class MainEngine;
typedef std::unique_ptr<MainEngine> upMainEngine;

class MainEngine :
        public MainEngineInterface
{
//____________________________________________Interface__
public:
    void setAccount(const spNode& node);

    void eventAddLL(const QVariant& name);
    void eventCreateDct(const QVariant& name);

    void eventSelectLL(const QVariant& name);
    void eventSelectDct(const QVariant& name);


//_______________________________________Initialization__
public:
    explicit MainEngine(upMainViewInterface&& view,
                        spFunctionalAccounts fAcs,
                        spFunctionalAccount fAc,
                        spFunctionalLL fLL,
                        upAdapterSimpleRef&& adapterLL,
                        upAdapterHideRows&& adapterLanguages,
                        upAdapterSimple&& adapterDct,
                        upAdapterWords&& adapterWords);
    ~MainEngine() = default;

private:
    void initialize_() override final;

//_______________________________________________Hidden__
private:
    spFunctionalAccounts fAcs_;
    spFunctionalAccount fAc_;
    spFunctionalLL fLL_;
    upAdapterSimpleRef adapterLL_;
    upAdapterHideRows adapterLanguages_;
    upAdapterSimple adapterDct_;
    upAdapterWords adapterWords_;

    spNode curAccount_;
    spNode curLL_;
    spNode curDct_;

private:
    void hideLangs();

    void setCurLL(const QVariant& name);
    void setCurDct(const QVariant& name);

    spNode account();
    spNode curLL();
    spNode curDct();
//_______________________________________________________
};

#endif // MAINENGINE_H
