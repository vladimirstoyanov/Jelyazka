#ifndef JELAYZKA_TRAYICONSTATE_H
#define JELAYZKA_TRAYICONSTATE_H

#include "state.hpp"

class TrayIconState: public Jelyazka::IState
{
    Q_OBJECT
public:
        TrayIconState () = default;
        virtual ~TrayIconState () = default;
        virtual QString   getName() const  override { return "TrayIconState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
        void hideTrayIcon();
        void showTrayIcon();
};

#endif
