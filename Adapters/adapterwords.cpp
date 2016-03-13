#ifndef ADAPTERWORDS_H
#include "adapterwords.h"
#endif

//______________________________________________________________Interface__

void AdapterWords::setNameTranslationLang(const QVariant& name)
{
    nameTranslationLang_ = name;
}

spNode AdapterWords::getNodeAt(int row)
{
    if(row < 0 || row >= list_.size())
        throw std::invalid_argument("AdapterSimple::getNodeAt");
    return list_.at(row).first;
}

QVariant AdapterWords::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() ||
        index.row() < 0 || index.row() >= list_.size() ||
        index.column() < 0 || index.column() >= columnCount_) return QVariant();
    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case Word:
            return list_.at(index.row()).first->data(keyWord_);
        case Transcrioption:
            return list_.at(index.row()).first->data(keyTranscription_);
        case Translation:
            return list_.at(index.row()).second;
        }
    }
    return QVariant();
}

QModelIndex AdapterWords::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid() ||
       row < 0 || row >= list_.size() ||
       column < 0 || column >= columnCount_) return QModelIndex();
    return createIndex(row, column);
}

QModelIndex AdapterWords::parent(const QModelIndex&) const
{
    return QModelIndex();
}

int AdapterWords::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : list_.size();
}

int AdapterWords::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : columnCount_;
}

QHash<int, QByteArray> AdapterWords::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = QObject::tr("Data1").toUtf8();
    roles[1] = QObject::tr("Data2").toUtf8();
    roles[2] = QObject::tr("Data3").toUtf8();
    return roles;
}

//_________________________________________________________Initialization__

AdapterWords::AdapterWords(const spDataBase& base,
                           const IDTypeNode& idtnWord,
                           const IDTypeNode& idtnLL,
                           const IDTypeNode& idtnLK,
                           const IDTypeLink& idtlRef,
                           int keyNameLang,
                           int keyWord,
                           int keyTranscription):
    AdapterModel(base),
    idtnWord_(idtnWord),
    idtnLL_(idtnLL),
    idtnLK_(idtnLK),
    idtlRef_(idtlRef),
    keyNameLang_(keyNameLang),
    keyWord_(keyWord),
    keyTranscription_(keyTranscription)
{
    argument(idtnWord.isValid());
    argument(idtnLL.isValid());
    argument(idtnLK.isValid());
    argument(idtlRef.isValid());
}

//_________________________________________________________________Hidden__

void AdapterWords::accept()
{
    beginResetModel();
    subAdapter_.unsubscribeAll();
    list_.clear();
    if(!node_){ endResetModel(); return; }
    //Получаем список слов из установленного словаря
    auto children = base_->getChildren(node_->getID(), idtnWord_);
    QString transl;
    for(auto i: children){
        transl.clear();
        //Получаем список частей речи из данного слова
        auto ps = base_->getChildren(i->getID());
        for(auto j: ps){
            //Получаем список переводов из данной части речи
            auto translations = base_->getChildren(j->getID());
            //Пополняем строку с переводами, проверяя принадлежат ли данные слова
            //интересующему языку
            for(auto t: translations)
                if(getNameLang(t) == nameTranslationLang_) transl += t->data(keyWord_).toString() + ", ";
        }
        list_.append(std::make_pair(i, transl));
        subAdapter_.subscribe(i.get());
    }
    endResetModel();
}

QVariant AdapterWords::getNameLang(const spNode& word)
{
    auto l = base_->getParent(word->getID(), idtnLL_);
    if(!l) l = base_->getParent(word->getID(), idtnLK_);
    logic(l);
    return base_->getParameterNodeRef(l->getID(), idtlRef_, keyNameLang_);
}
