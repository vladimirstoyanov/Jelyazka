#include "transition.hpp"

void Transition::addTransition (const QString &event, std::shared_ptr<IState> from_state, std::shared_ptr<IState> to_state)
{
    transitions_[event] = std::make_pair(from_state, to_state);
}

void Transition::makeTransition (std::shared_ptr <IState> current_state, const QString &event)
{
    std::map<QString, std::pair< std::shared_ptr<IState>, std::shared_ptr<IState> > >::iterator it;
    it = transitions_.find(event);
    if (it != transitions_.end())
    {
        if (current_state == it->second.first)
        {
            current_state->onExit ();
            current_state = it->second.second;
            current_state->onEntry();
            current_state->onState();
        }
    }
}
