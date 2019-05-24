#ifndef JELAYZKA_IDLESTATE_H
#define JELYAZKA_IDLESTATE_H

#include "state.hpp"

class IdleState: public Jelyazka::IState
{
    public:
        IdleState () {}
        virtual QString   getName() const { return "IdleState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
