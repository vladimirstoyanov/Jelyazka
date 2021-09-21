#ifndef JELAYZKA_RSSDATAUPDATEDSTATE_H
#define JELAYZKA_RSSDATAUPDATEDSTATE_H

#include "state.hpp"

class RssDataUpdatedState: public Jelyazka::IState
{
public:
        RssDataUpdatedState () = default;
        virtual ~RssDataUpdatedState () = default;
        virtual QString   getName() const override { return "RssDataUpdatedState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
};

#endif
