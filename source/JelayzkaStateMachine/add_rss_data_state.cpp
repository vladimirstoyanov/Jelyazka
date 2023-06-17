#include "add_rss_data_state.hpp"

void AddRssDataState::onEntry(const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
    emit (addRssData());
}

void AddRssDataState::onState(const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
}

void AddRssDataState::onExit (const QString &event)
{
    Q_UNUSED(event);
    qDebug()<<__PRETTY_FUNCTION__;
    emit (rssDataAdded());
}

