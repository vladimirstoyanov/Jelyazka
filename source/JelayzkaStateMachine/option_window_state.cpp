#include "option_window_state.hpp"

void OptionWindowState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showOptionWindow());
}

void OptionWindowState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void OptionWindowState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideOptionWindow());
}

