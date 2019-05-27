#include "remove_old_data_state.hpp"
#include "database.h"

void RemoveOldDataState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;

    //remove the old data
    DataBase data_base;
    data_base.dropRssDataTable();
    data_base.createTables();

    emit (removeOldDataFinished("RemoveOldDataFinished"));
}

void RemoveOldDataState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RemoveOldDataState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

