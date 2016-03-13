#include "languageswindow.h"
#include "ui_languageswindow.h"

LanguagesWindow::LanguagesWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LanguagesWindow)
{
    ui->setupUi(this);
}

LanguagesWindow::~LanguagesWindow()
{
    delete ui;
}

void LanguagesWindow::showWin(QAbstractItemModel* model,
                              std::function<void(const QVariant&)> f)
{
    argument(model);
    ui->lvLanguages->setModel(model);
    f_ = f;
    show();
}

void LanguagesWindow::on_pbOK_clicked()
{
    auto list = ui->lvLanguages->selectionModel()->selectedRows();
    for(auto i: list){
        f_(ui->lvLanguages->model()->data(i));
    }
    hide();
}

void LanguagesWindow::on_pbCancel_clicked()
{
    hide();
}
