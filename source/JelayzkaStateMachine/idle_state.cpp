#include "idle_state.hpp"


void IdleState::onEntry(const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
}

void IdleState::onState(const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
}

void IdleState::onExit (const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
}
