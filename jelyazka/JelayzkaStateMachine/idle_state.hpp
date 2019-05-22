#ifndef JELAYZKA_IDLESTATE_H
#define JELYAZKA_IDLESTATE_H

#include "state.hpp"

class IdleState: public IState
{
    public:
        IdleState () {}
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
