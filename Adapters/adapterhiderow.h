#ifndef ADAPTERHIDEROW_H
#define ADAPTERHIDEROW_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

class AdapterHideRow;
typedef std::unique_ptr<AdapterHideRow> upAdapterHideRow;

class AdapterHideRow :
        public AdapterSimple
{
//______________________________________________________________Interface__
public:
    void hideRow(const QVariant& value);

//_________________________________________________________Initialization__
public:
    AdapterHideRow(const spDataBase& base,
                   const IDTypeNode& idtnChildren,
                   int key);
    ~AdapterHideRow() = default;

//_________________________________________________________________Hidden__
private:
    spNode hideNode_;
    int hideRowNum_;
//_________________________________________________________________________
};

#endif // ADAPTERHIDEROW_H
