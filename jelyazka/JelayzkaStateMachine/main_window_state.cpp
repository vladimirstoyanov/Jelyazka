#include "main_window_state.hpp"


void MainWindowState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(showMainWindow());
}

void MainWindowState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void MainWindowState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(hideMainWindow());
}
