#ifndef BASEVIEW_H
#define BASEVIEW_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

template<class T>
class BaseView :
        public Counter
{
//______________________Interface__
public:
    virtual void showView() = 0;
    virtual void hideView() = 0;

//_________________Initialization__
public:
    virtual ~BaseView() = default;
    void setEngine(T* engine);
    void initialize();

protected:
    virtual void initialize_() = 0;

//_________________________Hidden__
protected:
    T* engine_ = nullptr;
    bool isInitialized_ = false;
//_________________________________
};

template<class T>
void BaseView<T>::setEngine(T* engine)
{
    if(!engine)
        throw std::invalid_argument("AccountViewInterface::setEngine");
    engine_ = engine;
}

template<class T>
void BaseView<T>::initialize()
{
    if(isInitialized_)
        throw std::logic_error("AccountEngineInterface::initialize (already initialized)");
    if(!engine_)
        throw std::logic_error("AccountViewInterface::initialize");
    initialize_();
    isInitialized_ = true;
}

#endif // BASEVIEW_H
