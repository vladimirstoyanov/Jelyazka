#include "about_window_state.hpp"

void AboutWindowState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(showAboutWindow());
}

void AboutWindowState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void AboutWindowState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(hideAboutWindow());
}

