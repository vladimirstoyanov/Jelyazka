#include "rss_search_window_state.hpp"

void RssSearchWindowState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showRssSearchWindow());
}

void RssSearchWindowState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RssSearchWindowState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideRssSearchWindow());
}
