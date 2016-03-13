#ifndef FUNCTIONALDCT_H
#include "functionaldct.h"
#endif

bool FunctionalDctArgs::check()
{
    if(!base_ ||
       !idtnWord_     .isValid() ||
       !idtnLL_       .isValid() ||
       !idtnLK_       .isValid() ||
       !idtnPS_       .isValid() ||
       !idtnRefPS_    .isValid() ||
       !idtlWordDct_  .isValid() ||
       !idtlWordLang_ .isValid() ||
       !idtlRefPS_    .isValid() ||
       !idtlRef_      .isValid()) return false;
    return true;
}

FunctionalDct::FunctionalDct(FunctionalDctArgs&& args) :
    a(std::move(args))
{
    argument(a.check());
}

spNode FunctionalDct::createWord(const spNode& dct,
                                 const QString& word,
                                 const QString& transcription)
{
    //Находим язык, которому принадлежит словарь
    auto lang = getRefLang(dct);
    //Создаем слово в узле-ссылке на язык
    auto id = a.base_->createUnique(lang->getID(), a.idtnWord_, a.idtlWordLang_, a.keyWord_, word);
    spNode w;
    if(!id.isValid()){
    //Если id не валидный, значит слово уже есть в языке, ищем это слово
        w = a.base_->findChild(lang->getID(), a.keyWord_, word, a.idtnWord_);
        logic(w);
    }
    else{
        //Если id валидный получаем сам узел
        w = a.base_->getNode(id);
        //Создаем связь со словарем
        a.base_->connectNodes(dct->getID(), w->getID(), a.idtlWordDct_);
        //Создаем узлы ссылки на части речи из соответствующего языка
        auto listPS = a.base_->getChildren(lang->getID(), a.idtnPS_);
        for(auto i: listPS){
            auto p = a.base_->createUniqueRef(w->getID(), a.idtnRefPS_, a.idtlRefPS_, a.idtlRef_, i->getID());
            logic(p.isValid());
        }
    }
    //Присваиваем значение транскрипции
    w->setData(a.keyTranscription_, transcription);
    return w;
}

spNode FunctionalDct::getRefLang(const spNode& dct)
{
    //Находим язык, которому принадлежит словарь
    auto l = a.base_->getParent(dct->getID(), a.idtnLL_);
    if(!l) l = a.base_->getParent(dct->getID(), a.idtnLK_);
    logic(l);
    return a.base_->getReferencingNode(l, a.idtlRef_);
}
