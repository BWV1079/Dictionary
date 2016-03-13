#ifndef CONTROLLERSETPARAMETER_H
#include "controllersetparameter.h"
#endif

ControllerSetParameter::ControllerSetParameter(int key):
    key_(key)
{}

void ControllerSetParameter::operator ()(const spNode& node,
                                         const QVariant& value) const
{
    if(!node)
        throw std::invalid_argument("ControllerSetParameter::setParameter");
    node->setData(key_, value);
}
