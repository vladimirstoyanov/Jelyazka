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

    void addTransition (const QString &event, std::shared_ptr<Jelyazka::IState> from_state, std::shared_ptr<Jelyazka::IState> to_state);
    void makeTransition (std::shared_ptr <Jelyazka::IState> current_state, const QString &event);

private:
    std::map <QString, std::pair< std::shared_ptr<Jelyazka::IState>, std::shared_ptr<Jelyazka::IState> > > transitions_;
};

#endif
