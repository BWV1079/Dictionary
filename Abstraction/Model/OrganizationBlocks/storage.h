#ifndef STORAGE_H
#define STORAGE_H

#ifndef DISTRIBUTORIDNODE_H
#include "distributoridnode.h"
#endif
#ifndef NODE_H
#include "../BuildingBlocks/node.h"
#endif

class Storage;
typedef std::unique_ptr<Storage> upStorage;

class Storage
{
//_________________________________________________Interface__
public:
    virtual ~Storage() = default;

public:
    virtual spDistributorIDNode getDistributorIDNode() = 0;
    virtual void appendNodeRoot(const spNode& node) = 0;
    virtual void appendNode(const spNode& node,
                            const IDNode& idParent) = 0;
    virtual void removeNode(const IDNode& id) = 0;
    virtual spNode getNode(const IDNode& id) = 0;
    virtual void beginChange() = 0;
    virtual void endChange() = 0;
    virtual void initialize() = 0;
//____________________________________________________________
};

#endif // STORAGE_H
