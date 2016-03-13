#ifndef ADDWORDVIEW_H
#define ADDWORDVIEW_H

#ifndef ADDWORDVIEWINTERFACE_H
#include "addword_viewinterface.h"
#endif
#ifndef TRANSLATIONGROUP_H
#include "translationgroup.h"
#endif

namespace Ui {
class AddWordView;
}

class AddWordView : public QWidget
{
    Q_OBJECT

public:
    explicit AddWordView(QWidget *parent = 0);
    ~AddWordView();

private:
    Ui::AddWordView *ui;
};

#endif // ADDWORDVIEW_H
