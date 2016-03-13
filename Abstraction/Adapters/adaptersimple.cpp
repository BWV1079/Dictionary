#ifndef ADAPTERSIMPLE_H
#include "adaptersimple.h"
#endif

//______________________________________________________________Interface__

spNode AdapterSimple::getNodeAt(int row)
{
    if(row < 0 || row >= list_.size())
        throw std::invalid_argument("AdapterSimple::getNodeAt");
    return list_.at(row);
}

QVariant AdapterSimple::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() ||
        index.row() < 0 || index.row() >= list_.size() ||
        index.column() < 0 || index.column() >= columnCount_) return QVariant();
    if(role == Qt::DisplayRole){
        return list_[index.row()]->data(key_);
    }
    return QVariant();
}

QModelIndex AdapterSimple::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid() ||
       row < 0 || row >= list_.size() ||
       column < 0 || column >= columnCount_) return QModelIndex();
    return createIndex(row, column);
}

QModelIndex AdapterSimple::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int AdapterSimple::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : list_.size();
}

int AdapterSimple::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : columnCount_;
}

QHash<int, QByteArray> AdapterSimple::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = QObject::tr("Data").toUtf8();
    return roles;
}

//_________________________________________________________Initialization__

AdapterSimple::AdapterSimple(const spDataBase& base,
                             const IDTypeNode& idtnChildren,
                             int key):
    AdapterModel(base),
    idtnChildren_(idtnChildren),
    key_(key)
{
    argument(idtnChildren_.isValid());
}

//_________________________________________________________________Hidden__

void AdapterSimple::accept()
{
    beginResetModel();
    subAdapter_.unsubscribeAll();
    list_.clear();
    if(!node_){ endResetModel(); return; }
    auto children = base_->getChildren(node_->getID(), idtnChildren_);
    for(auto i: children){
        list_.append(i);
        subAdapter_.subscribe(i.get());
    }
    endResetModel();
}
