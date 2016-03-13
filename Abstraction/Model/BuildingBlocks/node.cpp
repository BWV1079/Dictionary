#ifndef NODE_H
#include "node.h"
#endif

//_______________________________________Interface__

IDNode Node::getID() const
{
    if(!isInitialised_)
        throw std::logic_error("Node::getID");
    return id_;
}
IDTypeNode Node::getIDType() const
{
    if(!isInitialised_)
        throw std::logic_error("Node::getIDType");
    return idType_;
}
QList<IDNode> Node::getParents() const
{
    if(!isInitialised_)
        throw std::logic_error("Node::getParents");
    return parents_;
}
QList<spLink> Node::getLinks(const IDTypeLink& idtl)
{
    if(!isInitialised_)
        throw std::logic_error("Node::getLinks");
    if(!idtl.isValid()) return links_;
    QList<spLink> list;
    for(auto i = links_.begin(); i != links_.end(); ++i)
        if((*i)->getIDType() == idtl) list.append(*i);
    return list;
}
spLink Node::getLink(IDNode id)
{
    if(!isInitialised_)
        throw std::logic_error("Node::getLink");
    for(auto i: links_)
        if(i->getIDNodeEnd() == id) return i;
    return spLink();
}

void Node::copyParameters(const spNode& node)
{
    if(!node)
        throw std::invalid_argument("Node::copyParameters");
    if(idType_ != node->getIDType())
        throw std::logic_error("Node::copyParameters");
    ParametersContainer::operator =(*node);
}

//________________________________Private_Interface__

spLink Node::connect(const spNode& child,
                     std::function<upLink(const IDNode &, const IDNode &)> createLink)
{
    if(!isInitialised_)
        throw std::logic_error("Node::connect (initialization)");
    if(!child)
        throw std::invalid_argument("Node::connect");
    if(child.get() == this     ||
       child->getID() == id_   ||
       getLink(child->getID()) ||
       child->getParents().contains(id_))
        throw std::logic_error("Node::connect");
    auto link = createLink(id_, child->getID());
    auto result = appendLink(std::move(link));
    child->parents_.append(id_);
    changed();
    return result;
}

void Node::disconnect(const spNode& child)
{
    if(!isInitialised_)
        throw std::logic_error("Node::disconnect");
    if(!child)
        throw std::invalid_argument("Node::disconnect");
    auto l = getLink(child->getID());
    child->parents_.removeOne(id_);
    removeLink(l);
    changed();
}

//__________________________________Initialisation__

Node::Node(upParameters&& parameters,
           const IDNode& id,
           const IDTypeNode& idType):
    ParametersContainer(std::move(parameters))
{
    initialize(id, idType);
}

Node::Node(Node&& obj) :
    ParametersContainer(std::move(obj))
{
    move(std::move(obj));
}

Node& Node::operator =(Node&& obj)
{
    if(this != &obj){
        ParametersContainer::operator =(std::move(obj));
        move(std::move(obj));
    }
    return *this;
}

void Node::initialize(const IDNode& id,
                      const IDTypeNode& idType)
{
    if(!id.isValid() ||
       !idType.isValid())
        throw std::invalid_argument("Node::initialize");
    id_ = id;
    idType_ = idType;
    isInitialised_ = true;
}

void Node::move(Node&& obj)
{
    id_ = std::move(obj.id_);
    idType_ = std::move(obj.idType_);
    parents_ = std::move(obj.parents_);
    links_ = std::move(obj.links_);
    isInitialised_ = obj.isInitialised_;
    obj.parents_.clear();
    obj.links_.clear();
    obj.isInitialised_ = false;
}

QDataStream& operator <<(QDataStream& out, const Node& obj)
{
    if(!obj.isInitialised_)
        throw std::logic_error("QDataStream << Node");
    const ParametersContainer& p = obj;
    out << p;
    out << obj.parents_;
    out << obj.links_.size();
    for(auto i: obj.links_) out << *i;
    out << obj.id_;
    out << obj.idType_;
    return out;
}

QDataStream& operator >>(QDataStream& in, Node& obj)
{
    if(obj.isInitialised_)
        throw std::logic_error("QDataStream >> Node");
    ParametersContainer& p = obj;
    in >> p;
    in >> obj.parents_;
    int size;
    in >> size;
    for(int i = 0; i < size; ++i){
        upLink l(new Link());
        in >> *l;
        obj.appendLink(std::move(l));
    }
    IDNode id;
    IDTypeNode idType;
    in >> id;
    in >> idType;
    obj.initialize(id, idType);
    return in;
}

//___________________________________________Hidden__

spLink Node::appendLink(upLink&& link)
{
    subscribe(link.get());
    spLink l = std::move(link);
    links_.append(l);
    return l;
}

void Node::removeLink(const spLink& link)
{
    unsubscribe(link.get());
    links_.removeOne(link);
}

void Node::reaction()
{
    changed();
}
