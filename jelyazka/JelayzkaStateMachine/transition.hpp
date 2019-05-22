#ifndef JELAYZKA_TRANSITION_H
#define JELAYZKA_TRANSITION_H

#include <map>
#include <memory>

#include <QString>

#include "state.hpp"

class Transition
{
public:
    Transition () {}

    void addTransition (const QString &event, std::shared_ptr<IState> from_state, std::shared_ptr<IState> to_state);
    void makeTransition (std::shared_ptr <IState> current_state, const QString &event);

private:
    std::map <QString, std::pair< std::shared_ptr<IState>, std::shared_ptr<IState> > > transitions_;
};

#endif
