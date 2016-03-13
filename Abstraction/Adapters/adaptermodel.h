#ifndef ADAPTERMODEL_H
#define ADAPTERMODEL_H

#ifndef DATABASE_H
#include "../Model/OrganizationBlocks/database.h"
#endif

class SubAdapter:
        public Subscription
{
public:
    SubAdapter(std::function<void(void)> f);
    ~SubAdapter() = default;

private:
    std::function<void(void)> f_;

private:
    void reaction();
};


class AdapterModel:
        public Subscription,
        public QAbstractItemModel
{
//______________________________Interface__
public:
    void setNode(const spNode& node);
    spNode getNode();
    virtual spNode getNodeAt(int row) = 0;

//_________________________Initialization__
public:
    AdapterModel(const spDataBase& base);
    virtual ~AdapterModel() = default;

//_________________________________Hidden__
protected:
    SubAdapter subAdapter_;
    spDataBase base_;
    spNode node_;

protected:
    virtual void accept() = 0;
    void reaction() final override;
//_________________________________________
};

#endif // ADAPTERMODEL_H
