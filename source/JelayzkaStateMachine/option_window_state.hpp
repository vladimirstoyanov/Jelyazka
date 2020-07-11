#ifndef JELAYZKA_OPTIONWINDOWSTATE_H
#define JELAYZKA_OPTIONWINDOWSTATE_H

#include "state.hpp"

class OptionWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        OptionWindowState () {}
        virtual QString   getName() const { return "OptionWindowState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
    void hideOptionWindow ();
    void showOptionWindow ();
};

#endif
