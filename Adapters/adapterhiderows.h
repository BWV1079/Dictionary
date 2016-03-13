#ifndef ADAPTERHIDEROWS_H
#define ADAPTERHIDEROWS_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

class AdapterHideRows;
typedef std::unique_ptr<AdapterHideRows> upAdapterHideRows;

class AdapterHideRows :
        public AdapterSimple
{
//______________________________________________________________Interface__
public:
    void hideRows(QList<QVariant>&& values);

//_________________________________________________________Initialization__
public:
    AdapterHideRows(const spDataBase& base,
                    const IDTypeNode& idtnChildren,
                    int key,
                    QList<QVariant>&& listHide);
    ~AdapterHideRows() = default;

//_________________________________________________________________Hidden__
private:
    QList<QVariant> listHide_;

protected:
    void accept() override final;
//_________________________________________________________________________
};

#endif // ADAPTERHIDEROWS_H
