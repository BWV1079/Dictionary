#ifndef TYPELLFORDCTLK_H
#include "typellfordctlk.h"
#endif

upParameters TypeLLForDctLK::createParameters() const
{
    upParameters p (new Parameters());
    p->registerParameter(Name, "");
    return p;
}
