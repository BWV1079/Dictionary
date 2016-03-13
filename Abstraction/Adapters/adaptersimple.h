#ifndef ADAPTERSIMPLE_H
#define ADAPTERSIMPLE_H

#ifndef ADAPTERMODEL_H
#include "adaptermodel.h"
#endif

class AdapterSimple;
typedef std::unique_ptr<AdapterSimple> upAdapterSimple;
typedef std::shared_ptr<AdapterSimple> spAdapterSimple;

class AdapterSimple :
        public AdapterModel
{
//______________________________________________________________Interface__
public:
    spNode getNodeAt(int row);
    QVariant data(int row) const;

    QVariant data(const QModelIndex &index, int role) const override final;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const override final;
    QModelIndex parent(const QModelIndex&) const override final;
    int rowCount(const QModelIndex &parent) const override final;
    int columnCount(const QModelIndex &parent) const override final;
    QHash<int, QByteArray>  roleNames() const;

//_________________________________________________________Initialization__
public:
    AdapterSimple(const spDataBase& base,
                  const IDTypeNode& idtnChildren,
                  int key);
    virtual ~AdapterSimple() = default;

//_________________________________________________________________Hidden__
protected:
    QList<spNode> list_;
    const int columnCount_ = 1;
    IDTypeNode idtnChildren_;
    int key_;

protected:
    void accept() override;
//_________________________________________________________________________
};

#endif // ADAPTERSIMPLE_H
