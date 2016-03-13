#ifndef CONTROLLERGETPARAMETER_H
#include "controllergetparameter.h"
#endif

ControllerGetParameter::ControllerGetParameter(int key):
    key_(key)
{}

QVariant ControllerGetParameter::operator ()(const spNode& node) const
{
    if(!node)
        throw std::invalid_argument("ControllerGetParameter::operator ()");
    return node->data(key_);
}
