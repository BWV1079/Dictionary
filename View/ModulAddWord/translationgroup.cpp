#include "translationgroup.h"
#include "ui_translationgroup.h"

TranslationGroup::TranslationGroup(const QString& text,
                                   QAbstractItemModel* model,
                                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranslationGroup)
{
    argument(model);
    ui->setupUi(this);
    ui->label->setText(text);
    connect(model, SIGNAL(modelReset()), SLOT(resetModel()));
    ui->listView->setModel(model);
}

TranslationGroup::~TranslationGroup()
{
    delete ui;
}

void TranslationGroup::resetModel()
{
    if(ui->listView->model()->rowCount() > 0) show();
    else hide();
}
