#ifndef JELAYZKA_IDLESTATE_H
#define JELYAZKA_IDLESTATE_H

#include "state.hpp"

class IdleState: public Jelyazka::IState
{
    public:
        IdleState () {}
        virtual QString   getName() const { return "IdleState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
};

#endif
