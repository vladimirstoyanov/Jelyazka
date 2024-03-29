#include "transition.hpp"

void Transition::addTransition (const QString &event, std::shared_ptr<Jelyazka::IState> from_state, std::shared_ptr<Jelyazka::IState> to_state)
{
    transitions_[event] = std::make_pair(from_state, to_state);
}

void Transition::makeTransition (std::shared_ptr<Jelyazka::IState> &current_state, const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    std::map<QString, std::pair< std::shared_ptr<Jelyazka::IState>, std::shared_ptr<Jelyazka::IState> > >::iterator it;
    it = transitions_.find(event);
    if (it != transitions_.end())
    {
        if (current_state->getName() == it->second.first->getName())
        {
            qDebug()<<__PRETTY_FUNCTION__<<": making transition from "<<current_state->getName()<<" to "<<it->second.second->getName();
            current_state->onExit (event);
            current_state.reset();
            current_state = it->second.second;
            current_state->onEntry(event);
            current_state->onState(event);
        }
        else
        {
            current_state->onState(event);
        }
    }
}
