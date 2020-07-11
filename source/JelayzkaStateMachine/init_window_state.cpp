#include "init_window_state.hpp"

void InitWindowState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(showInitWindow());
}

void InitWindowState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void InitWindowState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (updateRssData());
    emit (hideInitWindow());
}
