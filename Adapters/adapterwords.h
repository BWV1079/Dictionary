#ifndef ADAPTERWORDS_H
#define ADAPTERWORDS_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../inclusion_for_dictionary.h"
#endif

class AdapterWords;
typedef std::unique_ptr<AdapterWords> upAdapterWords;

class AdapterWords :
        public AdapterModel
{
//______________________________________________________________Interface__
public:
    void setNameTranslationLang(const QVariant& name);
    spNode getNodeAt(int row);

    QVariant data(const QModelIndex &index, int role) const override final;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const override final;
    QModelIndex parent(const QModelIndex&) const override final;
    int rowCount(const QModelIndex &parent) const override final;
    int columnCount(const QModelIndex &parent) const override final;
    QHash<int, QByteArray>  roleNames() const;

//_________________________________________________________Initialization__
public:
    AdapterWords(const spDataBase& base,
                 const IDTypeNode& idtnWord,
                 const IDTypeNode& idtnLL,
                 const IDTypeNode& idtnLK,
                 const IDTypeLink& idtlRef,
                 int keyNameLang,
                 int keyWord,
                 int keyTranscription);
    virtual ~AdapterWords() = default;

//_________________________________________________________________Hidden__
protected:
    QList<std::pair<spNode, QString>> list_;
    enum ColumnNames{Word, Transcrioption, Translation};
    const int columnCount_ = 3;
    QVariant nameTranslationLang_;
    IDTypeNode idtnWord_;
    IDTypeNode idtnLL_;
    IDTypeNode idtnLK_;
    IDTypeLink idtlRef_;
    int keyNameLang_;
    int keyWord_;
    int keyTranscription_;

private:
    void accept() override final;
    QVariant getNameLang(const spNode& word);
//_________________________________________________________________________
};

#endif // ADAPTERWORDS_H
