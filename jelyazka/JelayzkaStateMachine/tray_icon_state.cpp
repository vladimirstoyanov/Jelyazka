#include "tray_icon_state.hpp"

void TrayIconState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(showTrayIcon());
}

void TrayIconState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void TrayIconState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(hideTrayIcon());
}

