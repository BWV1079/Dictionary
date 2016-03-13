#ifndef PARAMETERS_H
#define PARAMETERS_H

#ifndef INCLUSION_FOR_ABSTRACTION
#include "../../inclusion_for_abstraction.h"
#endif

class Parameters;
typedef std::unique_ptr<Parameters> upParameters;

class Parameters :
        public Counter
{
//______________________________________________Interface__
public:
    void registerParameter(int key, const QVariant& value);
    void setParameter(int key, const QVariant& value);
    QVariant getParameter(int key) const;
    QList<int> getKeys() const;
    int getParametersCount() const;

//_________________________________________Initialization__
public:
    friend QDataStream& operator<<(QDataStream& out,
                                   const Parameters& obj);
    friend QDataStream& operator>>(QDataStream& in,
                                   Parameters& obj);

//_________________________________________________Hidden__
private:
    QMap<int, QVariant> parameters_;
//_________________________________________________________
};

#endif // PARAMETERS_H
