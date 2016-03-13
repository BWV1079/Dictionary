#ifndef TYPEDCT_H
#include "typedct.h"
#endif

upParameters TypeDct::createParameters() const
{
    upParameters p (new Parameters());
    p->registerParameter(Name, "");
    return p;
}
