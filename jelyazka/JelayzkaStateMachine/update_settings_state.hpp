#ifndef JELAYZKA_UPDATESETTINGSSTATE_H
#define JELAYZKA_UPDATESETTINGSSTATE_H

#include "state.hpp"

class UpdateSettingsState: public Jelyazka::IState
{
    public:
        UpdateSettingsState () {}
        virtual QString   getName() const { return "UpdateSettingsState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
};

#endif
