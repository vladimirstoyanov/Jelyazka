#ifndef JELAYZKA_INITWINDOWSTATE_H
#define JELAYZKA_INITWINDOWSTATE_H

#include "state.hpp"

class InitWindowState: public IState
{
    public:
        InitWindowState () {}
        virtual QString   getName() const { return "InitWindowState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
