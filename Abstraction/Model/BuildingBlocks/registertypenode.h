#ifndef REGISTERTYPENODE_H
#define REGISTERTYPENODE_H

#ifndef CREATORNODE_H
#include "creatornode.h"
#endif

class RegisterTypeNode:
        public Counter
{
//__________________________________________________________Interface__
public:
    IDTypeNode registerNewType(const spCreatorNode& creator);
    spNode create(const IDNode& id,
                  const IDTypeNode& idType);

//_____________________________________________________Initialization__
public:
    RegisterTypeNode() = default;
    ~RegisterTypeNode() = default;
    RegisterTypeNode(const RegisterTypeNode& obj) = delete;
    RegisterTypeNode& operator =(const RegisterTypeNode& obj) = delete;

//_____________________________________________________________Hidden__
private:
    IDTypeNode idTypeLast_;
    QMap<IDTypeNode, spCreatorNode> creators_;
//_____________________________________________________________________
};

#endif // REGISTERTYPENODE_H
