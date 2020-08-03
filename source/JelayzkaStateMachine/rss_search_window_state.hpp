#ifndef JELAYZKA_RSSSEARCHWINDOWSTATE_H
#define JELAYZKA_RSSSEARCHWINDOWSTATE_H

#include "state.hpp"

class RssSearchWindowState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        RssSearchWindowState () = default;
        virtual ~RssSearchWindowState () = default;
        virtual QString   getName() const override { return "RssSearchWindowState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
    void hideRssSearchWindow ();
    void showRssSearchWindow ();
};

#endif
