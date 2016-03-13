#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#ifndef ACCOUNTVIEWINTERFACE_H
#include "account_viewinterface.h"
#endif

namespace Ui {
class AccountView;
}

class AccountView :
        public QWidget,
        public AccountViewInterface
{
    Q_OBJECT

public:
    explicit AccountView(QWidget *parent = 0);
    ~AccountView();

//______________AccountViewInterfaceAccount__

    void messageNameUserEmpty();
    void messageNameUserExist();
    void messageNameUserNotFound();

    void showView();
    void hideView();

    void setListLK(QAbstractItemModel* model);
    void setListLL(QAbstractItemModel* model);
    void initialize_();

//____________________________________
private:
    QAbstractItemModel* listLK_ = nullptr;
    QAbstractItemModel* listLL_ = nullptr;

private:
    void message(const QString& text);

private slots:
    void on_pbLogin_clicked();
    void on_pbRegister_clicked();
    void on_lwLK_clicked(const QModelIndex &index);
    void on_lwLL_clicked(const QModelIndex &index);

private:
    Ui::AccountView *ui;
};

#endif // ACCOUNTVIEW_H
