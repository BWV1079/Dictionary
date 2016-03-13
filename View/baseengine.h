#ifndef BASEENGINE_H
#define BASEENGINE_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

template<class T, class U>
class BaseEngine :
        public Counter
{
//_______________________________Interface__
public:
    void show();
    void hide();

//__________________________Initialization__
public:
    virtual ~BaseEngine() = default;
    void setView(std::unique_ptr<U>&& view);
    void initialize();

protected:
    virtual void initialize_() = 0;

//__________________________________Hidden__
protected:
    std::unique_ptr<U> view_;
    bool isInitialized_ = false;
//__________________________________________
};



//__________________________________________________Interface__

template<class T, class U>
void BaseEngine<T, U>::show()
{
    if(!isInitialized_)
        throw std::logic_error("AccountEngineInterface::show");
    view_->showView();
}

template<class T, class U>
void BaseEngine<T, U>::hide()
{
    if(!isInitialized_)
        throw std::logic_error("AccountEngineInterface::hide");
    view_->hideView();
}

//_____________________________________________Initialization__

template<class T, class U>
void BaseEngine<T, U>::setView(std::unique_ptr<U>&& view)
{
    if(!view)
        throw std::invalid_argument("AccountEngineInterface::setView");
    view_= std::move(view);
    view_->setEngine(static_cast<T*>(this));
}

template<class T, class U>
void BaseEngine<T, U>::initialize()
{
    if(isInitialized_)
        throw std::logic_error("AccountEngineInterface::initialize (already initialized)");
    if(!view_)
        throw std::logic_error("AccountEngineInterface::initialize");
    initialize_();
    isInitialized_ = true;
    view_->initialize();
}

#endif // BASEENGINE_H
