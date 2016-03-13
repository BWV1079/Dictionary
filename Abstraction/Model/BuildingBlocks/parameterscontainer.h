#ifndef PARAMETERSCONTAINER_H
#define PARAMETERSCONTAINER_H

#ifndef PARAMETERS_H
#include "parameters.h"
#endif
#ifndef SUBSCRIPTION_H
#include "../../Subscription/subscription.h"
#endif

class ParametersContainer :
        public Subscription
{
//______________________________________________________Interface__
public:
    QVariant data(int key) const;
    void setData(int key,
                 const QVariant& value);
    QList<int> getKeys() const;
    int getParametersCount() const;

//_________________________________________________Initialization__
protected:
    ParametersContainer() = default;
    explicit ParametersContainer(upParameters&& parameters);
    virtual ~ParametersContainer() = 0;
    ParametersContainer(const ParametersContainer& obj);
    ParametersContainer(ParametersContainer&& obj);
    ParametersContainer& operator =(const ParametersContainer& obj);
    ParametersContainer& operator =(ParametersContainer&& obj);

private:
    void initialize(upParameters&& parameters);
    void copy(const ParametersContainer& obj);
    void move(ParametersContainer& obj);

public:
    friend QDataStream& operator <<(QDataStream& out,
                                   const ParametersContainer& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                   ParametersContainer& obj);

//_________________________________________________________Hidden__
private:
    upParameters parameters_ = std::move(upParameters(new Parameters()));
    bool isInitialised_ = false;
//_________________________________________________________________
};

#endif // PARAMETERSCONTAINER_H
