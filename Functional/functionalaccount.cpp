#ifndef FUNCTIONALACCOUNT_H
#include "functionalaccount.h"
#endif

FunctionalAccount::FunctionalAccount(const spDataBase& base,
                                     const IDNode&     idLanguages,
                                     const IDTypeNode& idtnLK,
                                     const IDTypeNode& idtnLL,
                                     const IDTypeNode& idtnLanguage,
                                     const IDTypeNode& idtnLLForDctLK,
                                     const IDTypeLink& idtlLL,
                                     const IDTypeLink& idtlLLForDctLK,
                                     const IDTypeLink& idtlRef,
                                     int keyNameUser,
                                     int keyNameLang,
                                     int keyNameLLForDctLK,
                                     int keyCurLL) :
    base_             (base             ),
    idLanguages_      (idLanguages      ),
    idtnLK_       (idtnLK       ),
    idtnLL_       (idtnLL       ),
    idtnLanguage_     (idtnLanguage     ),
    idtnLLForDctLK_   (idtnLLForDctLK   ),
    idtlLL_           (idtlLL           ),
    idtlLLForDctLK_   (idtlLLForDctLK   ),
    idtlRef_          (idtlRef          ),
    keyNameUser_      (keyNameUser      ),
    keyNameLang_      (keyNameLang      ),
    keyNameLLForDctLK_(keyNameLLForDctLK),
    keyCurLL_         (keyCurLL         )
{
    argument(base_);
    argument(idLanguages_   .isValid());
    argument(idtnLK_    .isValid());
    argument(idtnLL_    .isValid());
    argument(idtnLanguage_  .isValid());
    argument(idtnLLForDctLK_.isValid());
    argument(idtlLL_        .isValid());
    argument(idtlLLForDctLK_.isValid());
    argument(idtlRef_       .isValid());
}

void FunctionalAccount::addLK(const spNode& account,
                                  const QString& nameLK)
{
    argument(account);
    logic(base_->getChildren(account->getID()).size() == 0);
    auto lang = base_->findChild(idLanguages_, keyNameLang_, nameLK);
    logic(lang);
    auto id = base_->createUniqueRef(account->getID(), idtnLK_, idtlLL_, idtlRef_, lang->getID());
    logic(id.isValid());
}

void FunctionalAccount::addLL(const spNode& account,
                                  const QString& nameLL)
{
    argument(account);
    // Находим в общем списке языков добавляемый язык по имени
    auto lang = base_->findChild(idLanguages_, keyNameLang_, nameLL);
    logic(lang);
    // Проверяем не свопадает ли он с родным языком
    auto children = base_->getChildren(account->getID(), idtnLK_);
    logic(children.size() == 1);
    auto links = children.first()->getLinks(idtlRef_);
    logic(links.size() == 1);
    logic((links.first()->getIDNodeEnd() != lang->getID()));
    // Создаем ссылочный узел и указываем на добавляеый язык
    base_->beginChange();
    auto id = base_->createUniqueRef(account->getID(), idtnLL_, idtlLL_, idtlRef_, lang->getID());
    logic(id.isValid());
    // Создаем дочерний узел с именем данного языка в узле для родного языка
    auto idLLForDctLK = base_->createUnique(children.first()->getID(),
                                            idtnLLForDctLK_,
                                            idtlLLForDctLK_,
                                            keyNameLLForDctLK_,
                                            nameLL);
    logic(idLLForDctLK.isValid());
    // Ставим этот язык текущим
    account->setData(keyCurLL_, nameLL);
    base_->endChange();
}

void FunctionalAccount::setCurLL(const spNode& account,
                                 const QString& nameLL)
{
    argument(account);
    auto list = getListNamesLL(account);
    logic(list.contains(nameLL));
    account->setData(keyCurLL_, nameLL);
}

spNode FunctionalAccount::getCurLL(const spNode& account)
{
    argument(account);
    auto name = getNameCurLL(account);
    auto n = base_->findChildRef(account->getID(), keyNameLang_, name, idtnLL_, idtlRef_);
    logic(n);
    return n;
}

spNode FunctionalAccount::getLK(const spNode& account)
{
    argument(account);
    auto children = base_->getChildren(account->getID(), idtnLK_);
    logic(children.size() == 1);
    return children.first();
}

QList<QVariant> FunctionalAccount::getListNamesLL(const spNode& account)
{
    argument(account);
    auto children = base_->getChildren(account->getID(), idtnLL_);
    QList<QVariant> list;
    for(auto i: children){
        list.append(base_->getParameterNodeRef(i->getID(), idtlRef_, keyNameLang_));
    }
    return list;
}

QVariant FunctionalAccount::getNameLK(const spNode& account)
{
    argument(account);
    auto children = base_->getChildren(account->getID(), idtnLK_);
    logic(children.size() == 1);
    return base_->getParameterNodeRef(children.first()->getID(), idtlRef_, keyNameLang_);
}

QVariant FunctionalAccount::getNameCurLL(const spNode& account)
{
    argument(account);
    return account->data(keyCurLL_);
}

QVariant FunctionalAccount::getNameUser(const spNode& account)
{
    argument(account);
    return account->data(keyNameUser_);
}
