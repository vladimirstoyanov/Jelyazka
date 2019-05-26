#ifndef JELAYZKA_INITWINDOWSTATE_H
#define JELAYZKA_INITWINDOWSTATE_H

#include "state.hpp"

class InitWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        InitWindowState () {}
        virtual QString getName() const { return "InitWindowState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
signals:

    void hideInitWindow ();
    void showInitWindow ();
    void updateRssData ();
};

#endif
