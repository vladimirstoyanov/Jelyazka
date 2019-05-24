#ifndef JELAYZKA_MAINWINDOWSTATE_H
#define JELAYZKA_MAINWINDOWSTATE_H

#include "state.hpp"

class MainWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        MainWindowState () {}
        virtual QString   getName() const { return "MainWindowState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
signals:
    void hideMainWindow ();
    void showMainWindow ();
};

#endif
