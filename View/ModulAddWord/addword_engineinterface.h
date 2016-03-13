#ifndef ADDWORDENGINEINTERFACE_H
#define ADDWORDENGINEINTERFACE_H

#ifndef BASEENGINE_H
#include "../baseengine.h"
#endif

class AddWordViewInterface;

class AddWordEngineInterface :
        public BaseEngine<AddWordEngineInterface, AddWordViewInterface>
{
//_____________________________________________________Interface__
public:
    virtual void setTranscription(const QVariant& text) = 0;
    virtual void appendTranslation(const QVariant& translation,
                                   const QVariant& ps) = 0;

//________________________________________________Initialization__
public:
    virtual ~AddWordEngineInterface() = default;

protected:
    virtual void initialize_() = 0;
//________________________________________________________________
};

#endif // ADDWORDENGINEINTERFACE_H
