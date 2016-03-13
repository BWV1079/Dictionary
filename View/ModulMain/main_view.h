#ifndef MAINVIEW_H
#define MAINVIEW_H

#ifndef LANGUAGESWINDOW_H
#include "languageswindow.h"
#endif
#ifndef MAINVIEWINTERFACE_H
#include "main_viewinterface.h"
#endif

namespace Ui {
class MainView;
}

class MainView :
        public QWidget,
        public MainViewInterface
{
    Q_OBJECT

public:
    void setNameUser(const QVariant& name);
    void setNameLK(const QVariant& name);
    void setNameCurLL(const QVariant& nameCurLL);
    void setModelLL(QAbstractItemModel* model);
    void setModelLanguages(QAbstractItemModel* model);
    void setModelDct(QAbstractItemModel* model);
    void setModelWords(QAbstractItemModel* model);

    void messageDctAlreadyExist();

    void showView();
    void hideView();

//_______________________________________________Initialization__
public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private:
    void initialize_();
    void message(const QString& text);

private slots:
    void on_pbAddLL_clicked();
    void on_cbLL_activated(const QString &arg1);
    void on_pbAddDct_clicked();
    void on_pbAddWord_clicked();

private:
    QAbstractItemModel* modelLanguages_ = nullptr;
    std::shared_ptr<LanguagesWindow> langWin_;

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
