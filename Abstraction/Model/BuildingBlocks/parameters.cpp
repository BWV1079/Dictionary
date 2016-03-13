#ifndef PARAMETERS_H
#include "parameters.h"
#endif

//______________________________________________Interface__

void Parameters::registerParameter(int key, const QVariant& value)
{
    if(parameters_.contains(key))
        throw std::invalid_argument("Parameters::registerParameter");
    parameters_.insert(key, value);
}

void Parameters::setParameter(int key, const QVariant& value)
{
    if(!parameters_.contains(key))
        throw std::invalid_argument("Parameters::setParameter");
    parameters_[key] = value;
}

QVariant Parameters::getParameter(int key) const
{
    if(!parameters_.contains(key))
        throw std::invalid_argument("Parameters::getParameter");
    return parameters_.value(key);
}

QList<int> Parameters::getKeys() const
{
    return parameters_.keys();
}

int Parameters::getParametersCount() const
{
    return parameters_.size();
}

//_________________________________________Initialization__

QDataStream& operator<<(QDataStream& out, const Parameters& obj)
{
    out << obj.parameters_;
    return out;
}

QDataStream& operator>>(QDataStream& in, Parameters& obj)
{
    in >> obj.parameters_;
    return in;
}

