#ifndef CONTROLLERFINDCHILD_H
#include "controllerfindchild.h"
#endif

ControllerFindChild::ControllerFindChild(const spDataBase& base,
                                         const IDTypeNode& idtnChildren,
                                         int key):
    base_(base),
    idtnChildren_(idtnChildren),
    key_(key)
{
    if(!base_ || !idtnChildren_.isValid())
        throw std::invalid_argument("ControllerFindChild::ControllerFindChild");
}

spNode ControllerFindChild::operator ()(const spNode& parent,
                                        const QVariant& value) const
{
    if(!parent)
        throw std::invalid_argument("ControllerFindChild::operator ()");
    auto children = base_->getChildren(parent->getID(), QList<IDTypeNode>()<<idtnChildren_);
    for(auto n: children)
        if(n->data(key_) == value) return n;
    return spNode();
}
