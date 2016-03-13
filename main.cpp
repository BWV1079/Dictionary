#ifndef INITIALIZATOR_H
#include "initializator.h"
#endif

int main(int argc, char *argv[])
{
    Initializator i(argc, argv);
    return i.initialize();
}
