#ifndef TYPEPARTOFSPEECH_H
#define TYPEPARTOFSPEECH_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

class TypePartOfSpeech :
        public CreatorNode
{
public:
    enum {Name};
    upParameters createParameters() const;
};

#endif // TYPEPARTOFSPEECH_H
