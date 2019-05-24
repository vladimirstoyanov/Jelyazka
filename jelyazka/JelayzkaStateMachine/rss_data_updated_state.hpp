#ifndef JELAYZKA_RSSDATAUPDATEDSTATE_H
#define JELAYZKA_RSSDATAUPDATEDSTATE_H

#include "state.hpp"

class RssDataUpdatedState: public Jelyazka::IState
{
    public:
        RssDataUpdatedState () {}
        virtual QString   getName() const { return "RssDataUpdatedState"; }
        virtual void onEntry();
        virtual void onState();
        virtual void onExit ();
};

#endif
