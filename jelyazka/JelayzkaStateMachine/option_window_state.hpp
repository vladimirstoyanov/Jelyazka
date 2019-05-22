#ifndef JELAYZKA_OPTIONWINDOWSTATE_H
#define JELAYZKA_OPTIONWINDOWSTATE_H

#include "state.hpp"

class OptionWindowState: public IState
{
    public:
        OptionWindowState () {}
        virtual QString   getName() const { return "OptionWindowState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
