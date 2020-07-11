#ifndef JELAYZKA_REMOVEOLDDATASTATE_H
#define JELAYZKA_REMOVEOLDDATASTATE_H

#include "state.hpp"

class RemoveOldDataState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        RemoveOldDataState () {}
        virtual QString   getName() const { return "RemoveOldDataState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
    signals:
        void removeOldDataFinished (const QString &);
};

#endif
