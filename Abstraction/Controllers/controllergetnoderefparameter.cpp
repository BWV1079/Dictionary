#ifndef CONTROLLERGETNODEREFPARAMETER_H
#include "controllergetnoderefparameter.h"
#endif

ControllerGetNodeRefParameter::ControllerGetNodeRefParameter(const spDataBase& base,
                                                             const IDTypeLink& idtlRef,
                                                             int key) :
    base_(base),
    idtlRef_(idtlRef),
    key_(key)
{
    if(!base_ || !idtlRef_.isValid())
        throw std::invalid_argument("ControllerGetNodeRefParameter::ControllerGetNodeRefParameter");
}

QVariant ControllerGetNodeRefParameter::operator ()(const spNode& node) const
{
    if(!node)
        throw std::invalid_argument("ControllerGetNodeRefParameter::operator ()");
    auto links = node->getLinks(idtlRef_);
    if(links.size() != 1)
        throw std::logic_error("ControllerGetNodeRefParameter::operator ()");
    auto n = base_->getNode(links.first()->getIDNodeEnd());
    return n->data(key_);
}
