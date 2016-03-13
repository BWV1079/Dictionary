#ifndef CONTROLLERCHECKPARAMETER_H
#include "controllercheckparameter.h"
#endif

ControllerCheckParameter::ControllerCheckParameter(int key):
    key_(key)
{}

bool ControllerCheckParameter::operator ()(const spNode& node,
                                           const QVariant& value) const
{
    if(!node)
        throw std::invalid_argument("ControllerCheckParameter::operator ()");
    return (node->data(key_) == value);
}
