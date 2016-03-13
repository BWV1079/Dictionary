#ifndef PARAMETERSCONTAINER_H
#include "parameterscontainer.h"
#endif

//______________________________________________________Interface__

QVariant ParametersContainer::data(int key) const
{
    if(!isInitialised_)
        throw std::logic_error("ParametersContainer::data");
    return parameters_->getParameter(key);
}

void ParametersContainer::setData(int key, const QVariant& value)
{
    if(!isInitialised_)
        throw std::logic_error("ParametersContainer::setData");
    parameters_->setParameter(key, value);
    changed();
}

QList<int> ParametersContainer::getKeys() const
{
    if(!isInitialised_)
        throw std::logic_error("ParametersContainer::getKeys");
    return parameters_->getKeys();
}

int ParametersContainer::getParametersCount() const
{
    if(!isInitialised_)
        throw std::logic_error("ParametersContainer::getParametersCount");
    return parameters_->getParametersCount();
}

//_________________________________________________Initialization__

ParametersContainer::ParametersContainer(upParameters&& parameters) :
    Subscription()
{
    initialize(std::move(parameters));
}

ParametersContainer::~ParametersContainer(){}

ParametersContainer::ParametersContainer(const ParametersContainer& obj) :
    Subscription(obj)
{
    copy(obj);
}

ParametersContainer::ParametersContainer(ParametersContainer&& obj) :
    Subscription(std::move(obj))
{
    move(obj);
}

ParametersContainer& ParametersContainer::operator =(const ParametersContainer& obj)
{
    if(this != &obj){
        Subscription::operator =(obj);
        copy(obj);
    }
    return *this;
}

ParametersContainer& ParametersContainer::operator =(ParametersContainer&& obj)
{
    if(this != &obj){
        Subscription::operator =(std::move(obj));
        move(obj);
    }
    return *this;
}

void ParametersContainer::initialize(upParameters&& parameters)
{
    if(!parameters)
        throw std::invalid_argument("ParametersContainer::ParametersContainer");
    parameters_ = std::move(parameters);
    isInitialised_ = true;
}

void ParametersContainer::copy(const ParametersContainer& obj)
{
    *parameters_ = *obj.parameters_;
    isInitialised_ = obj.isInitialised_;
}

void ParametersContainer::move(ParametersContainer& obj)
{
    parameters_ = std::move(obj.parameters_);
    isInitialised_ = obj.isInitialised_;
    obj.parameters_.reset(new Parameters());
    obj.isInitialised_ = false;
}

QDataStream& operator <<(QDataStream& out, const ParametersContainer& obj)
{
    if(!obj.isInitialised_)
        throw std::logic_error("QDataStream << ParametersContainer");
    out << *obj.parameters_;
    return out;
}

QDataStream& operator >>(QDataStream& in, ParametersContainer& obj)
{
    if(obj.isInitialised_)
        throw std::logic_error("QDataStream >> ParametersContainer");
    upParameters p(new Parameters());
    in >> *p;
    obj.initialize(std::move(p));
    return in;
}
