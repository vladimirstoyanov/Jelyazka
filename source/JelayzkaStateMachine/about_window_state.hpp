#ifndef JELAYZKA_ABOUTWINDOWSTATE_H
#define JELAYZKA_ABOUTWINDOWSTATE_H

#include "state.hpp"

class AboutWindowState: public Jelyazka::IState
{
    Q_OBJECT
public:
        AboutWindowState () = default;
        virtual ~AboutWindowState () = default;
        virtual QString   getName() const override { return "AboutWindowState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
        void hideAboutWindow();
        void showAboutWindow();

};

#endif
