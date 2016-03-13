#ifndef TRANSLATIONGROUP_H
#define TRANSLATIONGROUP_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

namespace Ui {
class TranslationGroup;
}

class TranslationGroup : public QWidget
{
    Q_OBJECT

public:
    explicit TranslationGroup(const QString& text,
                              QAbstractItemModel* model,
                              QWidget *parent = 0);
    ~TranslationGroup();

private slots:
    void resetModel();

private:
    Ui::TranslationGroup *ui;
};

#endif // TRANSLATIONGROUP_H
