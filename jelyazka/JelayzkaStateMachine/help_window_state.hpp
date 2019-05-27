#ifndef JELAYZKA_HELPWINDOWSTATE_H
#define JELAYZKA_HELPWINDOWSTATE_H

#include "state.hpp"

class HelpWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        HelpWindowState () {}
        virtual QString   getName() const { return "HelpWindowState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
    void hideHelpWindow ();
    void showHelpWindow ();
};

#endif
