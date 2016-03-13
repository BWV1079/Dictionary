#ifndef TYPEACCOUNT_H
#define TYPEACCOUNT_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

class TypeAccount:
        public CreatorNode
{
public:
    enum {NameUser, NameCurLL, RegistrationDate};
    upParameters createParameters() const;
};

#endif // TYPEACCOUNT_H
