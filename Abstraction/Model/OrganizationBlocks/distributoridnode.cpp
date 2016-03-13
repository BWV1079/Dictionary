#ifndef DISTRIBUTORIDNODE_H
#include "distributoridnode.h"
#endif

//____________________________________________________Interface__

IDNode DistributorIDNode::getID()
{
    if(idsFree_.isEmpty()){
        ++idLast_;
        return idLast_;
    }
    auto i = *idsFree_.begin();
    idsFree_.remove(i);
    return i;
}

void DistributorIDNode::removeID(IDNode id)
{
    if(idLast_ < id)
        throw std::invalid_argument("DistributorIDNode::removeID");
    idsFree_.insert(id);
}

//_______________________________________________Initialization__

QDataStream& operator <<(QDataStream& out, const DistributorIDNode& obj)
{
    out << obj.idLast_;
    out << obj.idsFree_;
    return out;
}

QDataStream& operator >>(QDataStream& in, DistributorIDNode& obj)
{
    in >> obj.idLast_;
    in >> obj.idsFree_;
    return in;
}

