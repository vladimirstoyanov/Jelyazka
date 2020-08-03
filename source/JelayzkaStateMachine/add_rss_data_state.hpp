#ifndef JELAYZKA_ADDRSSDATASTATE_H
#define JELAYZKA_ADDRSSDATASTATE_H

#include "state.hpp"

class AddRssDataState: public Jelyazka::IState
{
    Q_OBJECT
    public:
        AddRssDataState () = default;
        virtual ~AddRssDataState () = default;
        virtual QString   getName() const override { return "AddRssDataState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
        void rssDataAdded();
        void addRssData ();
};

#endif //JELAYZKA_ADDRSSDATASTATE_H
