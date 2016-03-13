#ifndef INCLUSION_FOR_ABSTRACTION
#include "inclusion_for_abstraction.h"
#endif

int Counter::n_ = 0;
int Counter::max_ = 0;

Counter::Counter()
{
    ++n_;
    ++max_;
}

Counter::~Counter()
{
    --n_;
    if(n_ == 0) std::cerr << "All (" << max_ << ") objects was deleted\n";
}
