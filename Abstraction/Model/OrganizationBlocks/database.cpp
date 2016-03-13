#ifndef DATABASE_H
#include "database.h"
#endif

//_______________________________________________Interface__

IDTypeNode DataBase::registerTypeNode(const spCreatorNode& creator)
{
    return nodesTypes_.registerNewType(creator);
}

IDTypeLink DataBase::registerTypeLink(const spCreatorLink& creator,
                                      bool force)
{
    return linksTypes_.registerNewType(creator, force);
}

spNode DataBase::getNode(const IDNode& id) const
{
    auto n = storage_->getNode(id);
    logic(n);
    return n;
}

IDNode DataBase::createNodeRoot(const IDTypeNode& idtn)
{
    argument(idtn.isValid());
    auto id = distributor_->getID();
    auto n = nodesTypes_.create(id, idtn);
    storage_->appendNodeRoot(n);
    return id;
}

spNode DataBase::createNode_(const IDTypeNode& idtn)
{
    auto id = distributor_->getID();
    auto n = nodesTypes_.create(id, idtn);
    return n;
}

IDNode DataBase::createNode(const IDNode& idParent,
                            const IDTypeNode& idtn,
                            const IDTypeLink& idtl)
{
    argument(idtn.isValid());
    argument(idtl.isValid());
    beginChange();
    auto p = getNode(idParent);
    auto n = createNode_(idtn);
    connectNodes_(p, n, idtl);
    storage_->appendNode(n, idParent);
    endChange();
    return n->getID();
}

IDNode DataBase::createUnique(const IDNode& idParent,
                              const IDTypeNode& idtn,
                              const IDTypeLink& idtl,
                              int keyUnique,
                              const QVariant& value)
{
    argument(idtn.isValid());
    argument(idtl.isValid());

    auto children = getChildren(idParent, idtn);
    for(auto n: children)
        if(n->data(keyUnique) == value) return IDNode();

    beginChange();
    auto p = getNode(idParent);
    auto n = createNode_(idtn);
    n->setData(keyUnique, value);
    storage_->appendNode(n, idParent);
    connectNodes_(p, n, idtl);
    endChange();

    return n->getID();
}

IDNode DataBase::createUniqueRef(const IDNode& idParent,
                                 const IDTypeNode& idtn,
                                 const IDTypeLink& idtl,
                                 const IDTypeLink& idtlRef,
                                 const IDNode& idRefNode)
{
    argument(idtn.isValid());
    argument(idtl.isValid());
    argument(idtlRef.isValid());
    argument(idRefNode.isValid());

    auto children = getChildren(idParent, idtn);
    for(auto n: children)
        if(getReferencingNode(n, idtlRef)->getID() == idRefNode) return IDNode();

    beginChange();
    auto p = getNode(idParent);
    auto r = getNode(idRefNode);
    auto n = createNode_(idtn);
    connectNodes_(n, r, idtlRef);
    storage_->appendNode(n, idParent);
    connectNodes_(p, n, idtl);
    endChange();

    return n->getID();
}

void DataBase::removeNode(const IDNode& id)
{

}

void DataBase::connectNodes(const IDNode& idBase,
                            const IDNode& idEnd,
                            const IDTypeLink& idtl)
{
    storage_->beginChange();
    auto nb = getNode(idBase);
    auto ne = getNode(idEnd);
    connectNodes_(nb, ne, idtl);
    storage_->endChange();
}

void DataBase::connectNodes_(const spNode& nb,
                             const spNode& ne,
                             const IDTypeLink& idtl)
{
    nb->connect(ne,
                [=](const IDNode& nBase, const IDNode& nEnd)->upLink{
                    return this->linksTypes_.create(idtl, nBase, nEnd);
                });
}

void DataBase::disconnectNodes(const IDNode& idParent,
                               const IDNode& idChild)
{

}

QList<spNode> DataBase::getChildren(const IDNode& idParent,
                                    const IDTypeNode& idtn) const
{
    auto p = getNode(idParent);
    QList<spNode> list;
    auto links = p->getLinks();
    for(auto i: links){
        auto n = getNode(i->getIDNodeEnd());
        if(idtn.isValid() && n->getIDType() != idtn) continue;
        list.append(n);
    }
    return list;
}

QList<spNode> DataBase::getParents(const IDNode& idChild,
                                   const IDTypeNode& idtn) const
{
    auto n = getNode(idChild);
    QList<spNode> list;
    auto idParents = n->getParents();
    for(auto i: idParents){
        auto p = getNode(i);
        if(idtn.isValid() && p->getIDType() != idtn) continue;
        list.append(p);
    }
    return list;
}

spNode DataBase::getParent(const IDNode& idChild,
                           const IDTypeNode& idtn) const
{
    auto list = getParents(idChild, idtn);
    logic(list.size() <= 1);
    return list.isEmpty() ? spNode() : list.first();
}

spNode DataBase::getReferencingNode(const spNode& nodeRef,
                                    const IDTypeLink& idtlRef)
{
    argument(nodeRef);
    argument(idtlRef.isValid());
    auto links = nodeRef->getLinks(idtlRef);
    logic(links.size() == 1);
    auto idr = links.first()->getIDNodeEnd();
    auto nr = getNode(idr);
    return nr;
}

QVariant DataBase::getParameterNodeRef(const IDNode& id,
                                       const IDTypeLink& idtlRef,
                                       int key)
{
    auto n = getNode(id);
    auto nr = getReferencingNode(n, idtlRef);
    return nr->data(key);
}

spNode DataBase::findChild(const IDNode& idParent,
                           int key,
                           const QVariant& value,
                           const IDTypeNode& idtn)
{
    auto children = getChildren(idParent, idtn);
    for(auto n: children)
        if(n->data(key) == value) return n;
    return spNode();
}

spNode DataBase::findChildRef(const IDNode& idParent,
                              int key,
                              const QVariant& value,
                              const IDTypeNode& idtn,
                              const IDTypeLink& idtlRef)
{
    auto children = getChildren(idParent, idtn);
    for(auto n: children){
        auto v = getParameterNodeRef(n->getID(), idtlRef, key);
        if(v == value) return n;
    }
    return spNode();
}

void DataBase::copyChildren(const spNode& nodeFrom,
                            const spNode& nodeTo)
{
    argument(nodeFrom);
    argument(nodeTo);
    auto links = nodeFrom->getLinks();
    beginChange();
    for(auto i: links){
        auto typeLink = i->getIDType();
        auto n = getNode(i->getIDNodeEnd());
        auto typeNode = n->getIDType();
        auto id = createNode(nodeTo->getID(), typeNode, typeLink);
        getNode(id)->copyParameters(n);
    }
    endChange();
}

void DataBase::beginChange()
{
    storage_->beginChange();
}

void DataBase::endChange()
{
    storage_->endChange();
}

//__________________________________________Initialization__

DataBase::DataBase(upStorage&& storage):
    storage_(std::move(storage))
{
    if(!storage_)
        throw std::invalid_argument("DataBase::DataBase");
    distributor_ = storage_->getDistributorIDNode();
    if(!distributor_)
        throw std::logic_error("DataBase::DataBase");
}

void DataBase::initialise()
{
    storage_->initialize();
}
