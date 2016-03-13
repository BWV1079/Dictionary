#ifndef ID_H
#define ID_H

#ifndef INCLUSION_FOR_ABSTRACTION
#include "../../inclusion_for_abstraction.h"
#endif

class IDBase /*:
        public Counter*/
{
//__________________________________________Interface__
public:
    bool isValid() const;
    void setDefault();

//_____________________________________Initialization__
public:
    IDBase() = default;
    virtual ~IDBase() = 0;
    IDBase(const IDBase& obj);
    IDBase& operator =(const IDBase& obj);
    IDBase(IDBase&& obj);
    IDBase& operator =(IDBase&& obj);

    IDBase& operator ++();
    IDBase& operator --();
    
    bool operator <(const IDBase& obj) const;
    bool operator ==(const IDBase& obj) const;
    bool operator !=(const IDBase& obj) const;
    
    friend QDataStream& operator <<(QDataStream& out,
                                    const IDBase& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                    IDBase& obj);
    friend uint qHash(const IDBase& obj);

//_____________________________________________Hidden__
public://!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    const int defaultValue_ = 0;
    int n_ = defaultValue_;
//_____________________________________________________
};


class IDNode: public IDBase {};
class IDTypeNode: public IDBase {};
class IDTypeLink: public IDBase {};

#endif // ID_H
