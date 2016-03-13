#ifndef TYPEWORD_H
#define TYPEWORD_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

class TypeWord :
        public CreatorNode
{
public:
    enum {Name, Transcription, DateAdd};
    upParameters createParameters() const;
};

#endif // TYPEWORD_H
