#include "main_view.h"
#include "ui_main_view.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    langWin_ = std::shared_ptr<LanguagesWindow>(new LanguagesWindow());
}

MainView::~MainView()
{
    delete ui;
}


void MainView::setNameUser(const QVariant& name)
{
    ui->lNameUser->setText(name.toString());
}

void MainView::setNameLK(const QVariant& name)
{
    ui->lLK->setText(name.toString());
}

void MainView::setNameCurLL(const QVariant& nameCurLL)
{
    ui->cbLL->setCurrentText(nameCurLL.toString());
}

void MainView::showView()
{
    show();
}

void MainView::hideView()
{
    hide();
}

//_______________________________________________Initialization__

void MainView::setModelLL(QAbstractItemModel* model)
{
    argument(model);
    ui->cbLL->setModel(model);
}

void MainView::setModelLanguages(QAbstractItemModel* model)
{
    modelLanguages_ = model;
}

void MainView::setModelDct(QAbstractItemModel* model)
{
    argument(model);
    ui->lvDct->setModel(model);
}

void MainView::setModelWords(QAbstractItemModel* model)
{
    ui->tvWords->setModel(model);
}

void MainView::messageDctAlreadyExist()
{
    message("dct name is already exist");
}

void MainView::initialize_()
{
    logic(modelLanguages_);
    logic(langWin_);
}

void MainView::message(const QString& text)
{
    QMessageBox m;
    m.setText(text);
    m.exec();
}

void MainView::on_pbAddLL_clicked()
{
    logic(isInitialized_);
    langWin_->showWin(modelLanguages_, [this](const QVariant& val){this->engine_->eventAddLL(val);});
}

void MainView::on_cbLL_activated(const QString& arg1)
{
    logic(isInitialized_);
    engine_->eventSelectLL(arg1);
}

void MainView::on_pbAddDct_clicked()
{
    logic(isInitialized_);
    engine_->eventCreateDct(ui->leDct->text());
    ui->leDct->clear();
}

void MainView::on_pbAddWord_clicked()
{
    logic(isInitialized_);

}
