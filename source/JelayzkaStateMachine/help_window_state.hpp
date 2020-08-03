#ifndef JELAYZKA_HELPWINDOWSTATE_H
#define JELAYZKA_HELPWINDOWSTATE_H

#include "state.hpp"

class HelpWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        HelpWindowState () = default;
        virtual ~HelpWindowState () = default;
        virtual QString   getName() const override { return "HelpWindowState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
    void hideHelpWindow ();
    void showHelpWindow ();
};

#endif
