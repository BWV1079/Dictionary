#ifndef TYPEDCT_H
#define TYPEDCT_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

class TypeDct:
        public CreatorNode
{
public:
    enum {Name};
    upParameters createParameters() const;
};

#endif // TYPEDCT_H
