#ifndef JELAYZKA_IDLESTATE_H
#define JELYAZKA_IDLESTATE_H

#include "state.hpp"

class IdleState: public Jelyazka::IState
{
public:
        IdleState () = default;
        virtual ~IdleState () = default;
        virtual QString   getName() const override { return "IdleState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
};

#endif
