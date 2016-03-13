#ifndef INITIALIZATOR_H
#include "initializator.h"
#endif

Initializator::Initializator(int & argc, char ** argv):
    QApplication(argc, argv)
{}

int Initializator::initialize()
{
    try{
        initialize_();
    }
    catch(std::invalid_argument ex){
        message(QString("invalid_argument ") + QString(ex.what()));
        return 0;
    }
    catch(std::logic_error ex){
        message(QString("logic_error ") + QString(ex.what()));
        return 0;
    }
    catch(...){
        message("Unexpected exception");
        return 0;
    }
    return exec();
}

bool Initializator::notify(QObject* obj, QEvent *e)
{
    bool answer = false;
    try{
        answer = QApplication::notify(obj, e);
    }
    catch(std::invalid_argument ex){
        message(QString("invalid_argument ") + QString(ex.what()));
        qApp->exit();
    }
    catch(std::logic_error ex){
        message(QString("logic_error ") + QString(ex.what()));
        qApp->exit();
    }
    catch(...){
        message("Unexpected exception");
        qApp->exit();
    }
    return answer;
}

void Initializator::initialize_()
{
    base_ = spDataBase(new DataBase(upStorage(new FileManager())));

    createTypesNodes();
    createTypesLinks();
    idRoot_ = base_->createNodeRoot(idtnRoot_);
    idAccounts_ = base_->createNode(idRoot_, idtnAccounts_, idtlStrong_);
    createPartsOfSpeech();
    createLanguages();

    createFunctional();

    createModulAccount();
    createModulMain();

    base_->initialise();
}

void Initializator::message(const QString& text)
{
    QMessageBox m;
    m.setText(text);
    m.exec();
}
