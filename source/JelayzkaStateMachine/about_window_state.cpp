#include "about_window_state.hpp"

void AboutWindowState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(showAboutWindow());
}

void AboutWindowState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void AboutWindowState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(hideAboutWindow());
}

