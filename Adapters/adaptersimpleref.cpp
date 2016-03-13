#ifndef ADAPTERSIMPLEREF_H
#include "adaptersimpleref.h"
#endif

AdapterSimpleRef::AdapterSimpleRef(const spDataBase& base,
                                   const IDTypeNode& idtnChildren,
                                   int key,
                                   const IDTypeLink idtlRef) :
    AdapterSimple(base, idtnChildren, key),
    idtlRef_(idtlRef)
{
    if(!idtlRef_.isValid())
        throw std::invalid_argument("AdapterSimpleRef::AdapterSimpleRef");
}

void AdapterSimpleRef::accept()
{
    beginResetModel();
    subAdapter_.unsubscribeAll();
    list_.clear();
    if(!node_){ endResetModel(); return; }
    auto children = base_->getChildren(node_->getID(), idtnChildren_);
    for(auto i: children){
        auto links = i->getLinks(idtlRef_);
        for(auto j: links){
            auto n = base_->getNode(j->getIDNodeEnd());
            list_.append(n);
            subAdapter_.subscribe(n.get());
        }
    }
    endResetModel();
}
