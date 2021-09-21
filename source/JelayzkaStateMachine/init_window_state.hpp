#ifndef JELAYZKA_INITWINDOWSTATE_H
#define JELAYZKA_INITWINDOWSTATE_H

#include "state.hpp"

class InitWindowState: public Jelyazka::IState
{
    Q_OBJECT
public:
        InitWindowState () = default;
        virtual ~InitWindowState () = default;
        virtual QString getName() const override { return "InitWindowState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:

    void hideInitWindow ();
    void showInitWindow ();
    void updateRssData ();
};

#endif
