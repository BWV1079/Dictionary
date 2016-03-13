#ifndef CONTROLLERCHECKPARAMETER_H
#define CONTROLLERCHECKPARAMETER_H

#ifndef NODE_H
#include "../Model/BuildingBlocks/node.h"
#endif

class ControllerCheckParameter;
typedef std::unique_ptr<ControllerCheckParameter> upControllerCheckParameter;

class ControllerCheckParameter :
        public Counter
{
public:
    ControllerCheckParameter(int key);

//_____________________________________Interface__
public:
    bool operator ()(const spNode& node,
                     const QVariant& value) const;
//________________________________________________

private:
    int key_ = 0;
};

#endif // CONTROLLERCHECKPARAMETER_H
