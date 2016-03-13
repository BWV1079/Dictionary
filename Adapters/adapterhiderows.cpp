#ifndef ADAPTERHIDEROWS_H
#include "adapterhiderows.h"
#endif

//______________________________________________________________Interface__

void AdapterHideRows::hideRows(QList<QVariant>&& values)
{
    listHide_ = values;
    accept();
}

//_________________________________________________________Initialization__

AdapterHideRows::AdapterHideRows(const spDataBase& base,
                                 const IDTypeNode& idtnChildren,
                                 int key,
                                 QList<QVariant>&& listHide):
    AdapterSimple(base, idtnChildren, key),
    listHide_(std::move(listHide))
{}

//_________________________________________________________________Hidden__

void AdapterHideRows::accept()
{
    beginResetModel();
    subAdapter_.unsubscribeAll();
    list_.clear();
    if(!node_){ endResetModel(); return; }
    auto children = base_->getChildren(node_->getID(), idtnChildren_);
    for(auto i: children){
        if(!listHide_.contains(i->data(key_))){
            list_.append(i);
            subAdapter_.subscribe(i.get());
        }
    }
    endResetModel();
}
