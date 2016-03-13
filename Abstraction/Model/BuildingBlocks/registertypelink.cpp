#ifndef REGISTERTYPELINK_H
#include "registertypelink.h"
#endif

//________________________________________________Interface__

IDTypeLink RegisterTypeLink::registerNewType(const spCreatorLink& creator, bool force)
{
    if(!creator)
        throw std::invalid_argument("RegisterTypeLink::registerNewType");
    ++idTypeLast_;
    std::pair<spCreatorLink, bool> p(creator, force);
    creators_.insert(idTypeLast_, p);
    return idTypeLast_;
}

upLink RegisterTypeLink::create(const IDTypeLink& idType,
                                const IDNode& idBase,
                                const IDNode& idEnd) const
{
    std::pair<spCreatorLink, bool> p = creators_.value(idType);
    if(!p.first)
        throw std::logic_error("RegisterTypeLink::create");
    return p.first->create(idType, idBase, idEnd, p.second);
}
