#ifndef REGISTERTYPENODE_H
#include "registertypenode.h"
#endif

//__________________________________________________________Interface__

IDTypeNode RegisterTypeNode::registerNewType(const spCreatorNode& creator)
{
    if(!creator)
        throw std::invalid_argument("RegisterTypeNode::registerNewType");
    ++idTypeLast_;
    creators_.insert(idTypeLast_, creator);
    return idTypeLast_;
}

spNode RegisterTypeNode::create(const IDNode& id,
                                const IDTypeNode& idType)
{
    auto p = creators_.value(idType);
    if(!p)
        throw std::logic_error("RegisterTypeNode::create");
    return p->create(id, idType);
}
