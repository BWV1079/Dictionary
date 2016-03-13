#ifndef ADDWORDENGINE_H
#include "addword_engine.h"
#endif

//____________________________________________Interface__

void AddWordEngine::setTranscription(const QVariant& text){}
void AddWordEngine::appendTranslation(const QVariant& translation,
                                      const QVariant& ps){}

//_______________________________________Initialization__

AddWordEngine::AddWordEngine(upAddWordViewInterface&& view,
                             const spNode& dctFirst,
                             const spNode& dctSecond,
                             const spNode& word,
                             upAdapterSimple&& aAllPS,
                             const QMap<QString, spAdapterSimple>& mapPS,
                             const spFunctionalLL& fLL,
                             const spFunctionalDct& fDct) :
    dctFirst_  (dctFirst ),
    dctSecond_ (dctSecond),
    word_      (word     ),
    mapPS_     (mapPS    ),
    fLL_       (fLL      ),
    fDct_      (fDct     ),
    aAllPS_    (std::move(aAllPS))
{
    argument(view);
    argument(dctFirst_);
    argument(dctSecond_);
    argument(aAllPS_);
    for(auto i: mapPS_){
        argument(i);
    }
    argument(fLL_);
    argument(fDct_);
    setView(std::move(view));
    view_->setListAllPS(aAllPS_.get());
    QMap<QString, QAbstractItemModel*> map;
    for(auto i = mapPS_.begin(); i != mapPS_.end(); ++i){
        map.insert(i.key(), i.value().get());
    }
    view_->setMapPS(map);
}

void AddWordEngine::initialize_(){}
