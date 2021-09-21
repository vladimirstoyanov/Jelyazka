#ifndef JELAYZKA_UPDATESETTINGSSTATE_H
#define JELAYZKA_UPDATESETTINGSSTATE_H

#include "state.hpp"

class UpdateSettingsState: public Jelyazka::IState
{
    Q_OBJECT
public:
        UpdateSettingsState () = default;
        virtual ~UpdateSettingsState () = default;
        virtual QString   getName() const override{ return "UpdateSettingsState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
        void settingsUpdated();
        void updateSettings ();
};

#endif
