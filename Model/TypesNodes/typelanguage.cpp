#ifndef TYPELANGUAGE_H
#include "typelanguage.h"
#endif

upParameters TypeLanguage::createParameters() const
{
    upParameters p(new Parameters());
    p->registerParameter(NameEng, "");
    p->registerParameter(NameShort, "");
    p->registerParameter(NameVernacular, "");
    p->registerParameter(TranscriptionSigns, "");
    return p;
}
