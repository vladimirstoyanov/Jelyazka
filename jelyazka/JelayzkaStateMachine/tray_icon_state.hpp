#ifndef JELAYZKA_TRAYICONSTATE_H
#define JELAYZKA_TRAYICONSTATE_H

#include "state.hpp"

class TrayIconState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        TrayIconState () {}
        virtual QString   getName() const { return "TrayIconState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
signals:
        void hideTrayIcon();
        void showTrayIcon();
};

#endif
