#ifndef MAINENGINEINTERFACE_H
#define MAINENGINEINTERFACE_H

#ifndef BASEENGINE_H
#include "../baseengine.h"
#endif

class MainViewInterface;

class MainEngineInterface :
        public BaseEngine<MainEngineInterface, MainViewInterface>
{
//____________________________________________________Interface__
public:
    virtual void setAccount(const spNode& node) = 0;
    virtual void eventAddLL(const QVariant& name) = 0;
    virtual void eventCreateDct(const QVariant& name) = 0;
    virtual void eventSelectLL(const QVariant& nameLL) = 0;
    virtual void eventSelectDct(const QVariant& nameDct) = 0;
    virtual void eventAddWord() = 0;

//_______________________________________________Initialization__
public:
    virtual ~MainEngineInterface() = default;

protected:
    virtual void initialize_() = 0;
//_______________________________________________________________
};

#endif // MAINENGINEINTERFACE_H
