#ifndef NODESPOOL_H
#include "nodespool.h"
#endif

//_____________________________________________Interface__

void NodesPool::appendNode(const spNode& node)
{
    if(!node)
        throw std::invalid_argument("NodesPool::append");
    if(nodes_.contains(node->getID()))
        throw std::logic_error("NodesPool::append");
    append(node);
}

void NodesPool::removeNode(const IDNode& id)
{
    auto n = nodes_.value(id);
    if(!n)
        throw std::logic_error("NodesPool::remove");
    remove(n);
}

spNode NodesPool::get(const IDNode& id)
{
    if(!contains(id))
        throw std::logic_error("NodesPool::get");
    return nodes_.value(id);
}

bool NodesPool::contains(const IDNode& id) const
{
    return nodes_.contains(id);
}

QList<IDNode> NodesPool::getIDNodes() const
{
    return nodes_.keys();
}

//________________________________________Initialization__

NodesPool::NodesPool(NodesPool&& obj) :
    Subscription(std::move(obj))
{
    move(std::move(obj));
}

NodesPool& NodesPool::operator=(NodesPool&& obj)
{
    if(this != &obj){
        Subscription::operator =(std::move(obj));
        move(std::move(obj));
    }
    return *this;
}

void NodesPool::move(NodesPool&& obj)
{
    nodes_ = std::move(obj.nodes_);
    obj.nodes_.clear();
}

QDataStream& operator <<(QDataStream& out, const NodesPool& obj)
{
    out << obj.nodes_.size();
    for(auto i: obj.nodes_) out << *i;
    return out;
}

QDataStream& operator >>(QDataStream& in, NodesPool& obj)
{
    if(obj.nodes_.size())
        throw std::logic_error("QDataStream >> NodesPool");
    int size;
    in >> size;
    for(int i = 0; i < size; ++i){
        auto n = upNode(new Node());
        in >> *n;
        obj.append(std::move(n));
    }
    return in;
}

//________________________________________________Hidden__

void NodesPool::append(const spNode& node)
{
    subscribe(node.get());
    nodes_.insert(node->getID(), node);
}

void NodesPool::remove(const spNode& node)
{
    unsubscribe(node.get());
    nodes_.remove(node->getID());
}

void NodesPool::reaction()
{
    changed();
}
