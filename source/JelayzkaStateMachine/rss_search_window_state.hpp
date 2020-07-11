#ifndef JELAYZKA_RSSSEARCHWINDOWSTATE_H
#define JELAYZKA_RSSSEARCHWINDOWSTATE_H

#include "state.hpp"

class RssSearchWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        RssSearchWindowState () {}
        virtual QString   getName() const { return "RssSearchWindowState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
    void hideRssSearchWindow ();
    void showRssSearchWindow ();
};

#endif
