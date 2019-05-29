#include "update_settings_state.hpp"

void UpdateSettingsState::onEntry(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (updateSettings ());
}

void UpdateSettingsState::onState(const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void UpdateSettingsState::onExit (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit(settingsUpdated());
}

