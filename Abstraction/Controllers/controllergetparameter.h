#ifndef CONTROLLERGETPARAMETER_H
#define CONTROLLERGETPARAMETER_H

#ifndef NODE_H
#include "../Model/BuildingBlocks/node.h"
#endif

class ControllerGetParameter;
typedef std::unique_ptr<ControllerGetParameter> upControllerGetParameter;

class ControllerGetParameter :
        public Counter
{
public:
    ControllerGetParameter(int key);

//______________________________________Interface__
public:
    QVariant operator ()(const spNode& node) const;
//_________________________________________________

private:
    int key_ = 0;
};

#endif // CONTROLLERGETPARAMETER_H
