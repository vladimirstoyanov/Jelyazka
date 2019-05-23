#ifndef JELAYZKA_HELPWINDOWSTATE_H
#define JELAYZKA_HELPWINDOWSTATE_H

#include "state.hpp"

class HelpWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        HelpWindowState () {}
        virtual QString   getName() const { return "HelpWindowState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
signals:
    void showHelpWindow ();
};

#endif
