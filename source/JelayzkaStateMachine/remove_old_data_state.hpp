#ifndef JELAYZKA_REMOVEOLDDATASTATE_H
#define JELAYZKA_REMOVEOLDDATASTATE_H

#include "state.hpp"

class RemoveOldDataState: public Jelyazka::IState
{
    Q_OBJECT
public:
        RemoveOldDataState () = default;
        virtual ~RemoveOldDataState () = default;
        virtual QString   getName() const override { return "RemoveOldDataState"; }
        virtual void onEntry(const QString &event) override;
        virtual void onState(const QString &event) override;
        virtual void onExit (const QString &event) override;
signals:
        void removeOldDataFinished (const QString &);
};

#endif
