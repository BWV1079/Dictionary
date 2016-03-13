#ifndef NODESPOOL_H
#define NODESPOOL_H

#ifndef NODE_H
#include "../BuildingBlocks/node.h"
#endif

class NodesPool;
typedef std::unique_ptr<NodesPool> upNodesPool;

class NodesPool:
        public Subscription
{
//_____________________________________________Interface__
public:
    void appendNode(const spNode &node);
    void removeNode(const IDNode& id);
    spNode get(const IDNode& id);
    bool contains(const IDNode& id) const;
    QList<IDNode> getIDNodes() const;

//________________________________________Initialization__
public:
    NodesPool() = default;
    ~NodesPool() = default;
    NodesPool(const NodesPool& obj) = delete;
    NodesPool& operator =(const NodesPool& obj) = delete;
    NodesPool(NodesPool&& obj);
    NodesPool& operator =(NodesPool&& obj);
    void move(NodesPool&& obj);

public:
    friend QDataStream& operator <<(QDataStream& out,
                                    const NodesPool& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                    NodesPool& obj);

//________________________________________________Hidden__
private:
    QMap<IDNode, spNode> nodes_;

private:
    void append(const spNode& node);
    void remove(const spNode& node);
    void reaction() final override;
//________________________________________________________
};

#endif // NODESPOOL_H
