#ifndef JELAYZKA_MAINWINDOWSTATE_H
#define JELAYZKA_MAINWINDOWSTATE_H

#include "state.hpp"

class MainWindowState: public Jelyazka::IState
{
    Q_OBJECT
public:
        MainWindowState () = default;
        virtual ~MainWindowState () = default;
        virtual QString getName() const override { return "MainWindowState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
    void hideMainWindow ();
    void showMainWindow ();
    void startRssRefreshData ();
};

#endif
