#include "account_view.h"
#include "ui_view_account.h"

AccountView::AccountView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountView)
{
    ui->setupUi(this);
}

AccountView::~AccountView()
{
    delete ui;
}

//_______________________________AccountViewInterfaceAccount__

void AccountView::messageNameUserEmpty()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::messageNameUserEmpty");
    message("messageNameUserEmpty");
}

void AccountView::messageNameUserExist()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::messageNameUserExist");
    message("messageNameUserExist");
}

void AccountView::messageNameUserNotFound()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::messageNameUserNotFound");
    message("messageNameUserNotFound");
}

void AccountView::showView()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::showView");
    show();
}

void AccountView::hideView()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::hideView");
    hide();
}

void AccountView::setListLK(QAbstractItemModel* model)
{
    if(!model)
        throw std::invalid_argument("AccountView::setListLK");
    listLK_ = model;
    ui->lwLK->setModel(listLK_);
}

void AccountView::setListLL(QAbstractItemModel* model)
{
    if(!model)
        throw std::invalid_argument("AccountView::setListLL");
    listLL_ = model;
    ui->lwLL->setModel(listLL_);
}

void AccountView::initialize_()
{
    if(!listLK_)
        throw std::logic_error("AccountView::initialize_");
    if(!listLL_)
        throw std::logic_error("AccountView::initialize_");
}

//_____________________________________________________

void AccountView::message(const QString& text)
{
    QMessageBox m;
    m.setText(text);
    m.exec();
}

void AccountView::on_pbLogin_clicked()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::on_pbLogin_clicked");
    engine_->eventLogin(ui->leNameUser->text());
}

void AccountView::on_pbRegister_clicked()
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::on_pbRegister_clicked");
    engine_->eventRegister(ui->leNameUser->text(),
                           ui->selectedLK->text(),
                           ui->selectedLL->text());
}

void AccountView::on_lwLK_clicked(const QModelIndex &index)
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::on_lwLK_clicked");
    auto text = ui->lwLK->model()->data(index, Qt::DisplayRole).toString();
    engine_->eventSelectedLK(text);
    ui->selectedLK->setText(text);
    ui->selectedLL->setText("");
}

void AccountView::on_lwLL_clicked(const QModelIndex &index)
{
    if(!isInitialized_)
        throw std::logic_error("AccountView::on_lwLL_clicked");
    ui->selectedLL->setText(ui->lwLL->model()->data(index, Qt::DisplayRole).toString());
}
