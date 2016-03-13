#ifndef FUNCTIONALLL_H
#include "functionalll.h"
#endif

bool FunctionalLLArgs::check()
{
    if(!base_ ||
       !idtnDct_.isValid() ||
       !idtnLLForDctLK_.isValid() ||
       !idtlDct_.isValid() ||
       !idtlLLForDctLK_.isValid() ||
       !idtlRef_.isValid()) return false;
    return true;
}

FunctionalLL::FunctionalLL(FunctionalLLArgs&& args) :
    a_(args)
{
    argument(a_.check());
}

spNode FunctionalLL::createDct(const spNode& ll,
                               const spNode& lk,
                               const QVariant& nameDct)
{
    argument(ll);
    argument(lk);
    //Создаем словарь в изучаемом языке
    auto id = a_.base_->createUnique(ll->getID(), a_.idtnDct_, a_.idtlDct_, a_.keyNameDct_, nameDct);
    //Если id не валидный, значит такой словарь уже есть
    if(!id.isValid()) return spNode();
    //Получаем название изучаемого языка
    auto nameLL = a_.base_->getParameterNodeRef(ll->getID(), a_.idtlRef_, a_.keyNameLang_);
    //Ищем дочерний узел в родном языке с названием изучаемого языка
    auto n = a_.base_->findChild(lk->getID(),
                                 a_.keyNameLLForDctLK_,
                                 nameLL,
                                 a_.idtnLLForDctLK_);
    logic(n);
    //Создаем в этом дочернем узле словарь с таким же названием
    auto d = a_.base_->createUnique(n->getID(), a_.idtnDct_, a_.idtlDct_, a_.keyNameDct_, nameDct);
    logic(d.isValid());
    //Связываем этот словарь с узлом родного языка непосредственно
    a_.base_->connectNodes(lk->getID(), d, a_.idtlDctLK_);
    return a_.base_->getNode(id);
}
