#ifndef JELAYZKA_OPTIONWINDOWSTATE_H
#define JELAYZKA_OPTIONWINDOWSTATE_H

#include "state.hpp"

class OptionWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        OptionWindowState () = default;
        virtual ~OptionWindowState () = default;
        virtual QString   getName() const override { return "OptionWindowState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
    void hideOptionWindow ();
    void showOptionWindow ();
};

#endif
