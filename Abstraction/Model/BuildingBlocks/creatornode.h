#ifndef CREATORNODE_H
#define CREATORNODE_H

#ifndef NODE_H
#include "node.h"
#endif

class CreatorNode;
typedef std::shared_ptr<CreatorNode> spCreatorNode;

class CreatorNode:
        public Counter
{
//_____________________________________Interface__
public:
    spNode create(const IDNode& id,
                  const IDTypeNode& idType) const;

//________________________________Initialisation__
public:
    CreatorNode() = default;
    virtual ~CreatorNode() = default;

//________________________________________Hidden__
protected:
    virtual upParameters createParameters() const;
//________________________________________________
};

#endif // CREATORNODE_H
