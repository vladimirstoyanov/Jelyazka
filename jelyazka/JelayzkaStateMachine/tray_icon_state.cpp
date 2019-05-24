#include "tray_icon_state.hpp"

void TrayIconState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(showTrayIcon());
}

void TrayIconState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void TrayIconState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(hideTrayIcon());
}

