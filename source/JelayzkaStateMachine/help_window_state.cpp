#include "help_window_state.hpp"

void HelpWindowState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showHelpWindow());
}

void HelpWindowState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void HelpWindowState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideHelpWindow());
}

