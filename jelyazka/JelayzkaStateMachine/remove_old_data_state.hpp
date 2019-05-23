#ifndef JELAYZKA_REMOVEOLDDATASTATE_H
#define JELAYZKA_REMOVEOLDDATASTATE_H

#include "state.hpp"

class RemoveOldDataState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        RemoveOldDataState () {}
        virtual QString   getName() const { return "RemoveOldDataState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
    signals:
        void removeOldDataFinished (const QString &);
};

#endif
