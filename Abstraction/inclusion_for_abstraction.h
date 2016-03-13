#ifndef INCLUSION_FOR_ABSTRACTION
#define INCLUSION_FOR_ABSTRACTION

#include <iostream>
#include <stdio.h>
#include <memory>
#include <functional>
#include <QDebug>
#include <QAbstractItemModel>
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <cassert>

class Counter
{
public:
    Counter();
    ~Counter();
    static int n_;
    static int max_;
};

#define EX
#ifdef EX
    #define logic(a) if(!(a)){ std::string text = std::string("Logic error\nfile: ") + __FILE__ + std::string("\nline: ") + std::to_string(__LINE__); throw std::logic_error(text); }
    #define argument(a) if(!(a)) { std::string text = std::string("Invalid argument\nfile: ") + __FILE__ + std::string("\nline: ") + std::to_string(__LINE__); throw std::invalid_argument(text); }
#else
    #define logic(a, b)
    #define argument(a, b)
#endif

#endif // INCLUSION_FOR_ABSTRACTION

