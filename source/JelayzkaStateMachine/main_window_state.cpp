#include "main_window_state.hpp"


void MainWindowState::onEntry(const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
    emit(startRssRefreshData());
    emit(showMainWindow());
}

void MainWindowState::onState(const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
}

void MainWindowState::onExit (const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
    emit(hideMainWindow());
}
