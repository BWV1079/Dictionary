#ifndef CONTROLLERSETPARAMETER_H
#define CONTROLLERSETPARAMETER_H

#ifndef NODE_H
#include "../Model/BuildingBlocks/node.h"
#endif

class ControllerSetParameter;
typedef std::unique_ptr<ControllerSetParameter> upControllerSetParameter;

class ControllerSetParameter :
        public Counter
{
public:
    ControllerSetParameter(int key);

//_____________________________________Interface__
public:
    void operator ()(const spNode& node,
                     const QVariant& value) const;
//________________________________________________

private:
    int key_ = 0;
};

#endif // CONTROLLERSETPARAMETER_H
