#ifndef CONTROLLERGETNODEREFPARAMETER_H
#define CONTROLLERGETNODEREFPARAMETER_H

#ifndef DATABASE_H
#include "../Model/OrganizationBlocks/database.h"
#endif

class ControllerGetNodeRefParameter;
typedef std::unique_ptr<ControllerGetNodeRefParameter> upControllerGetNodeRefParameter;

class ControllerGetNodeRefParameter :
        public Counter
{
public:
    ControllerGetNodeRefParameter(const spDataBase& base,
                                  const IDTypeLink& idtlRef,
                                  int key);

//_______________________________________________Interface__
public:
    QVariant operator ()(const spNode& node) const;
//__________________________________________________________

private:
    spDataBase base_;
    IDTypeLink idtlRef_;
    int key_ = 0;
};

#endif // CONTROLLERGETNODEREFPARAMETER_H
