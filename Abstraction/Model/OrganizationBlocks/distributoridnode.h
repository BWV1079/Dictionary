#ifndef DISTRIBUTORIDNODE_H
#define DISTRIBUTORIDNODE_H

#ifndef ID_H
#include "../BuildingBlocks/id.h"
#endif

class DistributorIDNode;
typedef std::shared_ptr<DistributorIDNode> spDistributorIDNode;

class DistributorIDNode :
        public Counter
{
//____________________________________________________Interface__
public:
    IDNode getID();
    void removeID(IDNode id);

//_______________________________________________Initialization__
public:
    friend QDataStream& operator <<(QDataStream& out,
                                   const DistributorIDNode& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                   DistributorIDNode& obj);

//_______________________________________________________Hidden__
private:
    QSet<IDNode> idsFree_;
    IDNode idLast_;
//_______________________________________________________________
};

#endif // DISTRIBUTORIDNODE_H
