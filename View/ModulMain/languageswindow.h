#ifndef LANGUAGESWINDOW_H
#define LANGUAGESWINDOW_H

#ifndef INCLUSION_FOR_DICTIONARY
#include "../../inclusion_for_dictionary.h"
#endif

namespace Ui {
class LanguagesWindow;
}

class LanguagesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LanguagesWindow(QWidget *parent = 0);
    ~LanguagesWindow();

    void showWin(QAbstractItemModel* model,
                 std::function<void(const QVariant&)> f);

private slots:
    void on_pbOK_clicked();
    void on_pbCancel_clicked();

private:
    std::function<void(const QVariant&)> f_;

private:
    Ui::LanguagesWindow *ui;
};

#endif // LANGUAGESWINDOW_H
