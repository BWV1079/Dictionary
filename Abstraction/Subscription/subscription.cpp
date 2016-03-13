#ifndef SUBSCRIPTION_H
#include "subscription.h"
#endif

//_____________________________________________Interface__

void Subscription::subscribe(Subscription* publisher)
{
    if(!publisher)
        throw std::invalid_argument("Subscription::subscribe");
    subscribe_(publisher);
}

void Subscription::unsubscribe(Subscription* publisher)
{
    publishers_.remove(publisher);
    if(publisher) publisher->removeSubscriber(this);
}

void Subscription::unsubscribeAll()
{
    auto s = std::move(subscribers_);
    for(auto i: s) i->unsubscribe(this);
    auto p = std::move(publishers_);
    for(auto i: p) unsubscribe(i);
}

//___________________________________Protected_Interface__

void Subscription::changed()
{
    isEnabled_ = false;
    for(auto i: subscribers_) i->reaction();
    isEnabled_ = true;
}

//________________________________________Initialization__

Subscription::~Subscription()
{
    unsubscribeAll();
}

Subscription::Subscription(const Subscription& obj)
{
    copy(obj);
}

Subscription::Subscription(Subscription&& obj)
{
    move(obj);
}

Subscription& Subscription::operator=(const Subscription& obj)
{
    if(this != &obj){
        unsubscribeAll();
        copy(obj);
    }
    return *this;
}

Subscription& Subscription::operator=(Subscription&& obj)
{
    if(this != &obj){
        unsubscribeAll();
        move(obj);
    }
    return *this;
}

void Subscription::copy(const Subscription& obj)
{
    for(auto i: obj.subscribers_) i->subscribe_(this);
    for(auto i: obj.publishers_) subscribe_(i);
}

void Subscription::move(Subscription& obj)
{
    copy(obj);
    obj.unsubscribeAll();
}

//________________________________________________Hidden__

void Subscription::subscribe_(Subscription* publisher)
{
    circularReferencesCheck(publisher);
    publishers_.insert(publisher);
    publisher->appendSubscriber(this);
}

void Subscription::circularReferencesCheck(Subscription* publisher)
{
    if(this == publisher)
        throw std::logic_error("Subscription::circularReferenceCheck");
    for(auto i: subscribers_)
        i->circularReferencesCheck(publisher);
}

void Subscription::appendSubscriber(Subscription* subscriber)
{
    if(!isEnabled_)
        throw std::logic_error("Subscription::appendSubscriber");
    subscribers_.insert(subscriber);
}

void Subscription::removeSubscriber(Subscription* subscriber)
{
    if(!isEnabled_)
        throw std::logic_error("Subscription::removeSubscriber");
    subscribers_.remove(subscriber);
}
