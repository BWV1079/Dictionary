#ifndef CONTROLLERCREATEUNIQUENODEREFERENCE_H
#define CONTROLLERCREATEUNIQUENODEREFERENCE_H

#ifndef DATABASE_H
#include "../Model/OrganizationBlocks/database.h"
#endif

class ControllerCreateUniqueNodeReference;
typedef std::unique_ptr<ControllerCreateUniqueNodeReference> upControllerCreateUniqueNodeReference;

class ControllerCreateUniqueNodeReference :
        public Counter
{
public:
    ControllerCreateUniqueNodeReference(const spDataBase& base,
                                        const IDTypeNode& idtnRef,
                                        const IDTypeLink& idtlRef,
                                        const IDTypeLink& idtlWithParent,
                                        QList<IDTypeNode>&& listTypesForMatching);

//____________________________________________________________Interface__
public:
    spNode operator ()(const spNode& parent,
                       const spNode& referencingNode) const;
//_______________________________________________________________________

private:
    spDataBase base_;
    IDTypeNode idtnRef_;
    IDTypeLink idtlRef_;
    IDTypeLink idtlWithParent_;
    QList<IDTypeNode> listTypesForMatching_;
};

#endif // CONTROLLERCREATEUNIQUENODEREFERENCE_H
