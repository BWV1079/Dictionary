#ifndef CREATORLINK_H
#define CREATORLINK_H

#ifndef LINK_H
#include "link.h"
#endif

class CreatorLink;
typedef std::shared_ptr<CreatorLink> spCreatorLink;

class CreatorLink:
        public Counter
{
//_____________________________________Interface__
public:
    upLink create(const IDTypeLink& idTypeLink,
                  const IDNode& idBase,
                  const IDNode& idEnd,
                  bool force) const;

//________________________________Initialisation__
public:
    CreatorLink() = default;
    virtual ~CreatorLink() = default;

//________________________________________Hidden__
protected:
    virtual upParameters createParameters() const;
//________________________________________________
};

#endif // CREATORLINK_H
