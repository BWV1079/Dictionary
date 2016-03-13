#ifndef CONTROLLERCREATEUNIQUENODEREFERENCE_H
#include "controllercreateuniquenodereference.h"
#endif

ControllerCreateUniqueNodeReference::ControllerCreateUniqueNodeReference(const spDataBase& base,
                                                                         const IDTypeNode& idtnRef,
                                                                         const IDTypeLink& idtlRef,
                                                                         const IDTypeLink& idtlWithParent,
                                                                         QList<IDTypeNode>&& listTypesForMatching) :
    base_          (base          ),
    idtnRef_       (idtnRef       ),
    idtlRef_       (idtlRef       ),
    idtlWithParent_(idtlWithParent),
    listTypesForMatching_ (std::move(listTypesForMatching))
{
    if(!base_ ||
       !idtnRef_.isValid() ||
       !idtlRef_.isValid() ||
       !idtlWithParent_.isValid())
        throw std::invalid_argument("ControllerCreateUniqueNodeReference::ControllerCreateUniqueNodeReference");
    if(listTypesForMatching_.size() != 0 &&
       !listTypesForMatching_.contains(idtnRef))
        throw std::logic_error("ControllerCreateUniqueNodeReference::ControllerCreateUniqueNodeReference");
}

spNode ControllerCreateUniqueNodeReference::operator ()(const spNode& parent,
                                                        const spNode& referencingNode) const
{
    if(!parent ||
       !referencingNode)
        throw std::invalid_argument("ControllerCreateUniqueNodeReference::operator ()");
    auto children = base_->getChildren(parent->getID(), listTypesForMatching_);
    for(auto n: children){
        auto links = n->getLinks(idtlRef_);
        if(links.size() != 1)
            throw std::logic_error("ControllerCreateUniqueNodeReference::operator()");
        if(links.first()->getIDNodeEnd() == referencingNode->getID())
            return spNode();
    }
    base_->beginChange();
    auto n = base_->createNode(idtnRef_, parent->getID(), idtlWithParent_);
    base_->connectNodes(n->getID(), referencingNode->getID(), idtlRef_);
    base_->endChange();
    return n;
}
