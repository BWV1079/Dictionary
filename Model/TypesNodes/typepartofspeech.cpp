#ifndef TYPEPARTOFSPEECH_H
#include "typepartofspeech.h"
#endif

upParameters TypePartOfSpeech::createParameters() const
{
    upParameters p(new Parameters());
    p->registerParameter(Name, "");
    return p;
}
