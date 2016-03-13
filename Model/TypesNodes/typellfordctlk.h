#ifndef TYPELLFORDCTLK_H
#define TYPELLFORDCTLK_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

class TypeLLForDctLK:
        public CreatorNode
{
public:
    enum {Name};
    upParameters createParameters() const;
};

#endif // TYPELLFORDCTLK_H
