#ifndef CONTROLLERCREATEUNIQUE_H
#define CONTROLLERCREATEUNIQUE_H

#ifndef DATABASE_H
#include "../Model/OrganizationBlocks/database.h"
#endif

class ControllerCreateUnique;
typedef std::unique_ptr<ControllerCreateUnique> upControllerCreateUnique;

class ControllerCreateUnique :
        public Counter
{
public:
    ControllerCreateUnique(const spDataBase& base,
                           const IDTypeNode& idtnChild,
                           const IDTypeLink& idtl,
                           int keyUnique);

//_________________________________________Interface__
public:
    spNode operator ()(const spNode& parent,
                       const QVariant& value) const;
//____________________________________________________

private:
    spDataBase base_;
    IDTypeNode idtnChild_;
    IDTypeLink idtl_;
    int keyUnique_ = 0;
};

#endif // CONTROLLERCREATEUNIQUE_H
