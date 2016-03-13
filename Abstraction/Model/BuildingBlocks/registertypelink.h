#ifndef REGISTERTYPELINK_H
#define REGISTERTYPELINK_H

#ifndef CREATORLINK_H
#include "creatorlink.h"
#endif

class RegisterTypeLink:
        public Counter
{
//__________________________________________________________Interface__
public:
    IDTypeLink registerNewType(const spCreatorLink& creator,
                               bool force);
    upLink create(const IDTypeLink& idType,
                  const IDNode& idBase,
                  const IDNode& idEnd) const;

//_____________________________________________________Initialization__
public:
    RegisterTypeLink() = default;
    ~RegisterTypeLink() = default;
    RegisterTypeLink(const RegisterTypeLink& obj) = delete;
    RegisterTypeLink& operator =(const RegisterTypeLink& obj) = delete;

//_____________________________________________________________Hidden__
private:
    IDTypeLink idTypeLast_;
    QMap<IDTypeLink, std::pair<spCreatorLink, bool>> creators_;
//_____________________________________________________________________
};

#endif // REGISTERTYPELINK_H
