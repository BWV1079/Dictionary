#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#ifndef INCLUSION_FOR_ABSTRACTION
#include "../inclusion_for_abstraction.h"
#endif

class Subscription :
        public Counter
{
//_____________________________________________Interface__
public:
    void subscribe(Subscription* publisher);
    void unsubscribe(Subscription* publisher);
    void unsubscribeAll();

//___________________________________Protected_Interface__
protected:
    void changed();
    virtual void reaction() = 0;

//________________________________________Initialization__
protected:
    Subscription() = default;
    virtual ~Subscription() = 0;
    Subscription(const Subscription& obj);
    Subscription(Subscription&& obj);
    Subscription& operator=(const Subscription& obj);
    Subscription& operator=(Subscription&& obj);

private:
    void copy(const Subscription& obj);
    void move(Subscription& obj);

//________________________________________________Hidden__
private:
    QSet<Subscription*> publishers_;
    QSet<Subscription*> subscribers_;
    bool isEnabled_ = true;

private:
    void subscribe_(Subscription* publisher);
    void circularReferencesCheck(Subscription* publisher);
    void appendSubscriber(Subscription* subscriber);
    void removeSubscriber(Subscription* subscriber);
//________________________________________________________
};

#endif // SUBSCRIPTION_H
