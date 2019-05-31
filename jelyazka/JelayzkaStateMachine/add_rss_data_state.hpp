#ifndef JELAYZKA_ADDRSSDATASTATE_H
#define JELAYZKA_ADDRSSDATASTATE_H

#include "state.hpp"

class AddRssDataState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        AddRssDataState () {}
        virtual QString   getName() const { return "AddRssDataState"; }
        virtual void onEntry(const QString &event);
        virtual void onState(const QString &event);
        virtual void onExit (const QString &event);
signals:
        void rssDataAdded();
        void addRssData ();
};

#endif //JELAYZKA_ADDRSSDATASTATE_H
