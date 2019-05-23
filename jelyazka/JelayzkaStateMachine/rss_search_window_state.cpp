#include "rss_search_window_state.hpp"

void RssSearchWindowState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showRssSearchWindow());
}

void RssSearchWindowState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RssSearchWindowState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}
