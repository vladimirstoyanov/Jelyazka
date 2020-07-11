#ifndef JELAYZKA_INITWINDOWSTATE_H
#define JELAYZKA_INITWINDOWSTATE_H

#include "state.hpp"

class InitWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        InitWindowState () {}
        virtual QString getName() const { return "InitWindowState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:

    void hideInitWindow ();
    void showInitWindow ();
    void updateRssData ();
};

#endif
