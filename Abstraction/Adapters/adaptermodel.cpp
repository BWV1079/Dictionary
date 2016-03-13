#ifndef ADAPTERMODEL_H
#include "adaptermodel.h"
#endif

SubAdapter::SubAdapter(std::function<void(void)> f) :
    f_(f)
{}

void SubAdapter::reaction()
{
    f_();
}

//______________________________Interface__

void AdapterModel::setNode(const spNode& node)
{
    if(node_ == node) return;
    unsubscribe(node_.get());
    node_ = node;
    if(node_) subscribe(node_.get());
    accept();
}

spNode AdapterModel::getNode()
{
    return node_;
}

//_________________________Initialization__

AdapterModel::AdapterModel(const spDataBase& base) :
    subAdapter_([this](){this->beginResetModel(); this->endResetModel();}),
    base_(base)
{
    argument(base_);
}

//_________________________________Hidden__

void AdapterModel::reaction()
{
    accept();
}
