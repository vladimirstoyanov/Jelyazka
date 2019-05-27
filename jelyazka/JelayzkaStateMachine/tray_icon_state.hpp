#ifndef JELAYZKA_TRAYICONSTATE_H
#define JELAYZKA_TRAYICONSTATE_H

#include "state.hpp"

class TrayIconState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        TrayIconState () {}
        virtual QString   getName() const { return "TrayIconState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
        void hideTrayIcon();
        void showTrayIcon();
};

#endif
