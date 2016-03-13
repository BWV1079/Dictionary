#ifndef CONTROLLERFINDCHILD_H
#define CONTROLLERFINDCHILD_H

#ifndef DATABASE_H
#include "../Model/OrganizationBlocks/database.h"
#endif

class ControllerFindChild;
typedef std::unique_ptr<ControllerFindChild> upControllerFindChild;

class ControllerFindChild :
        public Counter
{
public:
    ControllerFindChild(const spDataBase& base,
                        const IDTypeNode& idtnChildren,
                        int key);

//__________________________________________Interface__
public:
    spNode operator ()(const spNode& parent,
                       const QVariant& value) const;
//_____________________________________________________

private:
    spDataBase base_;
    IDTypeNode idtnChildren_;
    int key_ = 0;
};

#endif // CONTROLLERFINDCHILD_H
