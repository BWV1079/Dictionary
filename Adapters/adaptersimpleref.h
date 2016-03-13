#ifndef ADAPTERSIMPLEREF_H
#define ADAPTERSIMPLEREF_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

class AdapterSimpleRef;
typedef std::unique_ptr<AdapterSimpleRef> upAdapterSimpleRef;

class AdapterSimpleRef :
        public AdapterSimple
{
//______________________________________________________________Interface__
public:
    void hideRows(QList<QVariant>&& values);

//_________________________________________________________Initialization__
public:
    AdapterSimpleRef(const spDataBase& base,
                     const IDTypeNode& idtnChildren,
                     int key,
                     const IDTypeLink idtlRef);
    ~AdapterSimpleRef() = default;

//_________________________________________________________________Hidden__
private:
    IDTypeLink idtlRef_;

private:
    void accept() override final;
//_________________________________________________________________________
};

#endif // ADAPTERSIMPLEREF_H
