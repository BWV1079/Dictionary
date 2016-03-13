#ifndef TYPELANGUAGE_H
#define TYPELANGUAGE_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

class TypeLanguage :
        public CreatorNode
{
public:
    enum {NameEng, NameShort, NameVernacular, TranscriptionSigns};
    upParameters createParameters() const;
};

#endif // TYPELANGUAGE_H
