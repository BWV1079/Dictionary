#ifndef NODE_H
#define NODE_H

#ifndef LINK_H
#include "link.h"
#endif

class DataBase;
class CreatorNode;

class Node;
typedef std::shared_ptr<Node> spNode;
typedef std::unique_ptr<Node> upNode;

class Node:
        public ParametersContainer
{
//________________________________________Interface__
public:
    IDNode getID() const;
    IDTypeNode getIDType() const;
    QList<IDNode> getParents() const;
    spLink getLink(IDNode id);
    QList<spLink> getLinks(const IDTypeLink& idtl = IDTypeLink());
    void copyParameters(const spNode& node);

//________________________________Private_Interface__
private:
    spLink connect(const spNode& child,
                   std::function<upLink(const IDNode&, const IDNode&)> createLink);
    void disconnect(const spNode& child);

//___________________________________Initialisation__
public:
    Node() = default;
    ~Node() = default;

private:
    explicit Node(upParameters&& parameters,
                  const IDNode& id,
                  const IDTypeNode& idType);
    Node(const Node& obj) = delete;
    Node& operator =(const Node& obj) = delete;
    Node(Node&& obj);
    Node& operator =(Node&& obj);

    void initialize(const IDNode& id,
                    const IDTypeNode& idType);
    void move(Node&& obj);

public:
    friend class DataBase;
    friend class CreatorNode;
    friend QDataStream& operator <<(QDataStream& out,
                                    const Node& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                    Node& obj);

//___________________________________________Hidden__
private:
    IDNode id_;
    IDTypeNode idType_;
    QList<IDNode> parents_;
    QList<spLink> links_;
    bool isInitialised_ = false;

private:
    spLink appendLink(upLink&& link);
    void removeLink(const spLink& link);
    void reaction() final override;
//___________________________________________________
};

#endif // NODE_H
