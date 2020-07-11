#ifndef JELAYZKA_MAINWINDOWSTATE_H
#define JELAYZKA_MAINWINDOWSTATE_H

#include "state.hpp"

class MainWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        MainWindowState () {}
        virtual QString getName() const { return "MainWindowState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
    void hideMainWindow ();
    void showMainWindow ();
    void startRssRefreshData ();
};

#endif
