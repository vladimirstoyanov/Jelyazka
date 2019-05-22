#ifndef JELAYZKA_MAINWINDOWSTATE_H
#define JELAYZKA_MAINWINDOWSTATE_H

#include "state.hpp"

class MainWindowState: public IState
{
    public:
        MainWindowState () {}
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
