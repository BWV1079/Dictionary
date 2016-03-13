#ifndef LINK_H
#define LINK_H

#ifndef ID_H
#include "id.h"
#endif
#ifndef PARAMETERSCONTAINER_H
#include "parameterscontainer.h"
#endif

class CreatorLink;

class Link;
typedef std::shared_ptr<Link> spLink;
typedef std::unique_ptr<Link> upLink;

class Link :
        public ParametersContainer
{
//_______________________________________Interface__
public:
    IDTypeLink getIDType() const;
    IDNode getIDNodeBase() const;
    IDNode getIDNodeEnd() const;
    bool getForce() const;

//__________________________________Initialization__
public:
    Link() = default;
    ~Link() = default;

private:
    explicit Link(upParameters&& parameters,
                  const IDTypeLink& idType,
                  const IDNode& idBase,
                  const IDNode& idEnd,
                  bool force);
    Link(const Link& obj) = delete;
    Link& operator =(const Link& obj) = delete;
    Link(Link&& obj);
    Link& operator =(Link&& obj);

    void initialize(const IDTypeLink& idType,
                    const IDNode& idBase,
                    const IDNode& idEnd,
                    bool force);
    void move(Link&& obj);

public:
    friend class CreatorLink;
    friend QDataStream& operator <<(QDataStream& out,
                                   const Link& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                   Link& obj);

//__________________________________________Hidden__
private:
    IDTypeLink idType_;
    IDNode idBase_;
    IDNode idEnd_;
    bool force_ = false;
    bool isInitialised_ = false;

private:
    void reaction() final override;
//__________________________________________________
};

#endif // LINK_H
