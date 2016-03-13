#ifndef CONTROLLERCREATEUNIQUE_H
#include "controllercreateunique.h"
#endif

ControllerCreateUnique::ControllerCreateUnique(const spDataBase& base,
                                               const IDTypeNode& idtnChild,
                                               const IDTypeLink& idtl,
                                               int keyUnique) :
    base_(base),
    idtnChild_(idtnChild),
    idtl_(idtl),
    keyUnique_(keyUnique)
{
    if(!base_                ||
       !idtnChild_.isValid() ||
       !idtl_.isValid())
        throw std::invalid_argument("ControllerCreateUnique::ControllerCreateUnique");
}

spNode ControllerCreateUnique::operator ()(const spNode& parent,
                                           const QVariant& value) const
{
    if(!parent)
        throw std::invalid_argument("ControllerCreateUnique::operator ()");
    auto children = base_->getChildren(parent->getID(), idtnChild_);
    for(auto n: children)
        if(n->data(keyUnique_) == value) return spNode();
    base_->beginChange();
    auto n = base_->createNode(parent->getID(), idtnChild_, idtl_);
    n->setData(keyUnique_, value);
    base_->endChange();
    return n;
}
