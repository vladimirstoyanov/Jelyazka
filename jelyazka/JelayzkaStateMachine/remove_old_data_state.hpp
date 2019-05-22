#ifndef JELAYZKA_REMOVEOLDDATASTATE_H
#define JELAYZKA_REMOVEOLDDATASTATE_H

#include "state.hpp"

class RemoveOldDataState: public IState
{
    public:
        RemoveOldDataState () {}
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
