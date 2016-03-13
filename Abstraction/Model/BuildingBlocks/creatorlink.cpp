#ifndef CREATORLINK_H
#include "creatorlink.h"
#endif

//_____________________________Private_Interface__

upLink CreatorLink::create(const IDTypeLink& idTypeLink,
                           const IDNode& idBase,
                           const IDNode& idEnd,
                           bool force) const
{
    return upLink( new Link(createParameters(),
                            idTypeLink,
                            idBase,
                            idEnd,
                            force) );
}

//________________________________________Hidden__

upParameters CreatorLink::createParameters() const
{
    return upParameters(new Parameters());
}
