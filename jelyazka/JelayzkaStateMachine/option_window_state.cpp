#include "option_window_state.hpp"

void OptionWindowState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showOptionWindow());
}

void OptionWindowState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void OptionWindowState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

