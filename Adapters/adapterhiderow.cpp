#ifndef ADAPTERHIDEROW_H
#include "adapterhiderow.h"
#endif

//______________________________________________________________Interface__

void AdapterHideRow::hideRow(const QVariant& value)
{
    if(list_.isEmpty()) return;
    beginResetModel();
    if(hideNode_)
        list_.insert(hideRowNum_, hideNode_);
    auto i = std::find_if(list_.begin(), list_.end(),
                          [&](const spNode& n){
                                return (n->data(key_) == value);
                          });
    if(i == list_.end())
        throw std::logic_error("AdapterHideRow::hideRow");
    hideRowNum_ = list_.indexOf(*i);
    hideNode_ = *i;
    list_.removeAt(hideRowNum_);
    endResetModel();
}

//_________________________________________________________Initialization__

AdapterHideRow::AdapterHideRow(const spDataBase& base,
                               const IDTypeNode& idtnChildren,
                               int key):
    AdapterSimple(base, idtnChildren, key)
{}
