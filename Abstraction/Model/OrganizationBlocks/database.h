#ifndef DATABASE_H
#define DATABASE_H

#ifndef STORAGE_H
#include "storage.h"
#endif
#ifndef REGISTERTYPELINK_H
#include "../BuildingBlocks/registertypelink.h"
#endif
#ifndef REGISTERTYPENODE_H
#include "../BuildingBlocks/registertypenode.h"
#endif

class DataBase;
typedef std::shared_ptr<DataBase> spDataBase;

class DataBase :
        public Counter
{
//_______________________________________________Interface__
public:
    IDTypeNode registerTypeNode(const spCreatorNode& creator);
    IDTypeLink registerTypeLink(const spCreatorLink& creator,
                                bool force);

    spNode getNode(const IDNode& id) const;

    IDNode createNodeRoot(const IDTypeNode& idtn);
    IDNode createNode(const IDNode& idParent,
                      const IDTypeNode& idtn,
                      const IDTypeLink& idtl);
    IDNode createUnique(const IDNode& idParent,
                        const IDTypeNode& idtn,
                        const IDTypeLink& idtl,
                        int keyUnique,
                        const QVariant& value);
    IDNode createUniqueRef(const IDNode& idParent,
                           const IDTypeNode& idtn,
                           const IDTypeLink& idtl,
                           const IDTypeLink& idtlRef,
                           const IDNode& idReferencingNode);

    void removeNode(const IDNode& id);

    void connectNodes(const IDNode& idBase,
                      const IDNode& idEnd,
                      const IDTypeLink& idtl);
    void disconnectNodes(const IDNode& idParent,
                         const IDNode& idChild);

    QList<spNode> getChildren(const IDNode& idParent,
                              const IDTypeNode& idtn = IDTypeNode()) const;
    QList<spNode> getParents(const IDNode& idChild,
                             const IDTypeNode& idtn = IDTypeNode()) const;
    spNode getParent(const IDNode& idChild,
                     const IDTypeNode& idtn) const;
    spNode getReferencingNode(const spNode& nodeRef,
                              const IDTypeLink& idtlRef);
    QVariant getParameterNodeRef(const IDNode& id,
                                 const IDTypeLink& idtlRef,
                                 int key);

    spNode findChild(const IDNode& idParent,
                     int key,
                     const QVariant& value,
                     const IDTypeNode& idtn = IDTypeNode());
    spNode findChildRef(const IDNode& idParent,
                        int key,
                        const QVariant& value,
                        const IDTypeNode& idtn,
                        const IDTypeLink& idtlRef);

    void copyChildren(const spNode& nodeFrom,
                      const spNode& nodeTo);

    void beginChange();
    void endChange();

//__________________________________________Initialization__
public:
    DataBase(upStorage&& storage);
    ~DataBase() = default;

    void initialise();

//__________________________________________________Hidden__
private:
    upStorage storage_;
    spDistributorIDNode distributor_;
    RegisterTypeNode nodesTypes_;
    RegisterTypeLink linksTypes_;

private:
    void connectNodes_(const spNode& nb,
                       const spNode& ne,
                       const IDTypeLink& idtl);
    spNode createNode_(const IDTypeNode& idtn);
//__________________________________________________________
};

#endif // DATABASE_H
