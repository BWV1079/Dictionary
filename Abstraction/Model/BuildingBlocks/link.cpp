#ifndef LINK_H
#include "link.h"
#endif

//_______________________________________Interface__

bool Link::getForce() const
{
    if(!isInitialised_)
        throw std::logic_error("Link::getForce");
    return force_;
}

IDNode Link::getIDNodeBase() const
{
    if(!isInitialised_)
        throw std::logic_error("Link::getIDNodeBase");
    return idBase_;
}

IDNode Link::getIDNodeEnd() const
{
    if(!isInitialised_)
        throw std::logic_error("Link::getIDNodeEnd");
    return idEnd_;
}

IDTypeLink Link::getIDType() const
{
    if(!isInitialised_)
        throw std::logic_error("Link::getIDType");
    return idType_;
}

//__________________________________Initialization__

Link::Link(upParameters&& parameters,
           const IDTypeLink& idType,
           const IDNode& idBase,
           const IDNode& idEnd,
           bool force) :
    ParametersContainer(std::move(parameters))
{
    initialize(idType, idBase, idEnd, force);
}

Link::Link(Link&& obj) :
    ParametersContainer(std::move(obj))
{
    move(std::move(obj));
}

Link& Link::operator =(Link&& obj)
{
    if(this != &obj){
        ParametersContainer::operator =(std::move(obj));
        move(std::move(obj));
    }
    return *this;
}

void Link::initialize(const IDTypeLink& idType,
                      const IDNode& idBase,
                      const IDNode& idEnd,
                      bool force)
{
    if(!idType.isValid() ||
       !idBase.isValid() ||
       !idEnd.isValid())
        throw std::invalid_argument("Link::initialize");
    if(idBase == idEnd)
        throw std::logic_error("Link::initialize");
    idType_ = idType;
    idBase_ = idBase;
    idEnd_ = idEnd;
    force_ = force;
    isInitialised_ = true;
}

void Link::move(Link&& obj)
{
    idType_ = std::move(obj.idType_);
    idBase_ = std::move(obj.idBase_);
    idEnd_ = std::move(obj.idEnd_);
    force_ = obj.force_;
    obj.force_ = false;
    isInitialised_ = obj.isInitialised_;
    obj.isInitialised_ = false;
}

QDataStream& operator <<(QDataStream& out, const Link& obj)
{
    if(!obj.isInitialised_)
        throw std::logic_error("QDataStream << Link");
    const ParametersContainer& p = obj;
    out << p;
    out << obj.idType_;
    out << obj.idBase_;
    out << obj.idEnd_;
    out << obj.force_;
    return out;
}

QDataStream& operator >>(QDataStream& in, Link& obj)
{
    if(obj.isInitialised_)
        throw std::logic_error("QDataStream >> Link");
    ParametersContainer& p = obj;
    in >> p;
    IDTypeLink idType;
    IDNode idBase;
    IDNode idEnd;
    bool force;
    in >> idType;
    in >> idBase;
    in >> idEnd;
    in >> force;
    obj.initialize(idType, idBase, idEnd, force);
    return in;
}

//__________________________________________Hidden__

void Link::reaction(){}
