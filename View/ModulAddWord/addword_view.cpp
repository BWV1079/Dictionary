#include "addword_view.h"
#include "ui_addword_view.h"

AddWordView::AddWordView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWordView)
{
    ui->setupUi(this);
}

AddWordView::~AddWordView()
{
    delete ui;
}
