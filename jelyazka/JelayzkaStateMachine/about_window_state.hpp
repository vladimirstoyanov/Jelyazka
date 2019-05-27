#ifndef JELAYZKA_ABOUTWINDOWSTATE_H
#define JELAYZKA_ABOUTWINDOWSTATE_H

#include "state.hpp"

class AboutWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        AboutWindowState () {}
        virtual QString   getName() const { return "AboutWindowState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
        void hideAboutWindow();
        void showAboutWindow();

};

#endif
