#include "help_window_state.hpp"

void HelpWindowState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showHelpWindow());
}

void HelpWindowState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void HelpWindowState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

