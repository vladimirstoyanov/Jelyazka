#ifndef JELAYZKA_UPDATESETTINGSSTATE_H
#define JELAYZKA_UPDATESETTINGSSTATE_H

#include "state.hpp"

class UpdateSettingsState: public IState
{
    public:
        UpdateSettingsState () {}
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
