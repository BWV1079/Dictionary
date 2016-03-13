#ifndef TYPEACCOUNT_H
#include "typeaccount.h"
#endif

upParameters TypeAccount::createParameters() const
{
    upParameters p (new Parameters());
    p->registerParameter(NameUser, "");
    p->registerParameter(NameCurLL, "");
    p->registerParameter(RegistrationDate, QDateTime::currentDateTime());
    return p;
}
