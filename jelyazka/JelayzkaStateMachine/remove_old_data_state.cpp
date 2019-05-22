#include "remove_old_data_state.hpp"
#include "database.h"

void RemoveOldDataState::onEntry()
{
    qDebug()<<__PRETTY_FUNCTION__;
    //remove the old data
    DataBase data_base;
    data_base.dropRssDataTable();
    //ToDo: send an event: RemoveOldDataFinished
}

void RemoveOldDataState::onState()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RemoveOldDataState::onExit ()
{
    qDebug()<<__PRETTY_FUNCTION__;


}

