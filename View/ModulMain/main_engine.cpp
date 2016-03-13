#ifndef MAINENGINE_H
#include "main_engine.h"
#endif

void MainEngine::setAccount(const spNode& node)
{
    logic(isInitialized_);
    argument(node);

    adapterLL_->setNode(node);
    curAccount_ = node;
    view_->setNameUser(fAc_->getNameUser(account()));
    view_->setNameLK(fAc_->getNameLK(account()));
    hideLangs();
    setCurLL(fAc_->getNameCurLL(account()));
}

void MainEngine::setCurLL(const QVariant& name)
{
    view_->setNameCurLL(name);
    curLL_ = fAc_->getCurLL(account());
    adapterDct_->setNode(curLL_);

}

void MainEngine::setCurDct(const QVariant& name)
{

}

void MainEngine::eventSelectLL(const QVariant& name)
{
    logic(isInitialized_);
    fAc_->setCurLL(account(), name.toString());
    setCurLL(name);
}

void MainEngine::eventSelectDct(const QVariant &name)
{
    logic(isInitialized_);

}

void MainEngine::eventAddLL(const QVariant& name)
{
    logic(isInitialized_);
    fAc_->addLL(account(), name.toString());
    hideLangs();
    setCurLL(name);
}

void MainEngine::eventCreateDct(const QVariant& name)
{
    logic(isInitialized_);
    if(name.toString().isEmpty()) return;
    auto n = fLL_->createDct(curLL(), fAc_->getLK(account()), name);
    if(!n) view_->messageDctAlreadyExist();
}

MainEngine::MainEngine(upMainViewInterface&& view,
                       spFunctionalAccounts fAcs,
                       spFunctionalAccount fAc,
                       spFunctionalLL fLL,
                       upAdapterSimpleRef&& adapterLL,
                       upAdapterHideRows&& adapterLanguages,
                       upAdapterSimple&& adapterDct,
                       upAdapterWords&& adapterWords) :
    fAcs_(fAcs),
    fAc_(fAc),
    fLL_(fLL),
    adapterLL_(std::move(adapterLL)),
    adapterLanguages_(std::move(adapterLanguages)),
    adapterDct_(std::move(adapterDct)),
    adapterWords_(std::move(adapterWords))
{
    argument(fAcs_);
    argument(fAc_);
    argument(fLL_);
    argument(adapterLL_);
    argument(adapterLanguages_);
    argument(adapterDct_);
    argument(adapterWords_);
    setView(std::move(view));
    view_->setModelLL(adapterLL_.get());
    view_->setModelLanguages(adapterLanguages_.get());
    view_->setModelDct(adapterDct_.get());
    view_->setModelWords(adapterWords_.get());
}

void MainEngine::initialize_(){}

void MainEngine::hideLangs()
{
    logic(isInitialized_);
    QList<QVariant> list;
    list = fAc_->getListNamesLL(account());
    list.append(fAc_->getNameLK(account()));
    adapterLanguages_->hideRows(std::move(list));
}

spNode MainEngine::account()
{
    logic(curAccount_);
    return curAccount_;
}

spNode MainEngine::curLL()
{
    logic(curLL_);
    return curLL_;
}

spNode MainEngine::curDct()
{
    logic(curDct_);
    return curDct_;
}
