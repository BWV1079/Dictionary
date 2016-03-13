
#ifndef TYPEWORD_H
#include "typeword.h"
#endif

upParameters TypeWord::createParameters() const
{
    upParameters p(new Parameters());
    p->registerParameter(Name, "");
    p->registerParameter(Transcription, "");
    p->registerParameter(DateAdd, QDateTime::currentDateTime());
    return p;
}
