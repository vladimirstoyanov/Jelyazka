#ifndef JELAYZKA_RSSSEARCHWINDOWSTATE_H
#define JELAYZKA_RSSSEARCHWINDOWSTATE_H

#include "state.hpp"

class RssSearchWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        RssSearchWindowState () {}
        virtual QString   getName() const { return "RssSearchWindowState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
signals:
    void showRssSearchWindow ();
};

#endif
