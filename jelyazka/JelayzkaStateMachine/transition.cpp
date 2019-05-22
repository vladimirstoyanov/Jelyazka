#include "transition.hpp"

void Transition::addTransition (const QString &event, std::shared_ptr<IState> from_state, std::shared_ptr<IState> to_state)
{
    transitions_[event] = std::make_pair(from_state, to_state);
}

void Transition::makeTransition (std::shared_ptr <IState> current_state, const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    std::map<QString, std::pair< std::shared_ptr<IState>, std::shared_ptr<IState> > >::iterator it;
    it = transitions_.find(event);
    if (it != transitions_.end())
    {
        if (current_state->getName() == it->second.first->getName())
        {
            qDebug()<<__PRETTY_FUNCTION__<<": making transition from "<<current_state->getName()<<" to "<<it->second.second->getName();
            current_state->onExit ();
            current_state = it->second.second;
            current_state->onEntry();
            current_state->onState();
        }
    }
}
