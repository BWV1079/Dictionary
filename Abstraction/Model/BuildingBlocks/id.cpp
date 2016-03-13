#ifndef ID_H
#include "id.h"
#endif

bool IDBase::isValid() const {
    return n_;}

void IDBase::setDefault() {
    n_ = defaultValue_;}

IDBase::~IDBase(){}

IDBase::IDBase(const IDBase& obj) :
    n_(obj.n_)
{}

IDBase& IDBase::operator =(const IDBase& obj)
{
    if(this != &obj)
        n_ = obj.n_;
    return *this;
}

IDBase::IDBase(IDBase&& obj) :
    n_(obj.n_)
{
    obj.n_ = defaultValue_;
}

IDBase& IDBase::operator =(IDBase&& obj)
{
    if(this != &obj){
        n_ = obj.n_;
        obj.n_ = defaultValue_;
    }
    return *this;
}

IDBase& IDBase::operator ++() {
    ++n_; return *this;}

IDBase& IDBase::operator --() {
    --n_; return *this;}

bool IDBase::operator <(const IDBase& obj) const {
    return n_ < obj.n_;}

bool IDBase::operator ==(const IDBase& obj) const {
    return n_ == obj.n_;}

bool IDBase::operator !=(const IDBase& obj) const {
    return n_ != obj.n_;}

QDataStream& operator <<(QDataStream& out, const IDBase& obj)
{
    out << obj.n_;
    return out;
}

QDataStream& operator >>(QDataStream& in, IDBase& obj)
{
    in >> obj.n_;
    return in;
}

uint qHash(const IDBase& obj)
{
    return obj.n_;
}
