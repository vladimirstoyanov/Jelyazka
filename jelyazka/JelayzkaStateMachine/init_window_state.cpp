#include "init_window_state.hpp"

void InitWindowState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;

    //ToDo: send an event to show "InitWindow"
    emit(showInitWindow());
}

void InitWindowState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void InitWindowState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}
