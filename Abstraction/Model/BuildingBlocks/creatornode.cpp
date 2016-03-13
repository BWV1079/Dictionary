#ifndef CREATORNODE_H
#include "creatornode.h"
#endif

//_____________________________________Interface__

spNode CreatorNode::create(const IDNode& id, const IDTypeNode& idType) const
{
    return spNode( new Node(createParameters(), id, idType) );
}

//________________________________________Hidden__

upParameters CreatorNode::createParameters() const
{
    return upParameters(new Parameters());
}
