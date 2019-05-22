#include "jelyazka_state_machine.hpp"

JelayzkaStateMachine::JelayzkaStateMachine ():
    current_state_              (std::make_shared<IdleState> ())
    , idle_state_               (std::make_shared<IdleState> ())
    , init_window_state_        (std::make_shared<InitWindowState> ())
    , main_window_state_        (std::make_shared<MainWindowState> ())
    , option_window_state_      (std::make_shared<OptionWindowState> ())
    , remove_old_data_state_    (std::make_shared<RemoveOldDataState> ())
    , rss_data_updated_state_   (std::make_shared<RssDataUpdatedState> ())
    , transitions_              ()
    , update_settings_state_    (std::make_shared<UpdateSettingsState> ())
{
    //ToDo: add transitions
    transitions_.addTransition("RemoveOldData", idle_state_, remove_old_data_state_);
    transitions_.addTransition("RemoveOldDataFinished", remove_old_data_state_, init_window_state_);
    transitions_.addTransition("RSSDataDownloaded", init_window_state_, main_window_state_);
    transitions_.addTransition("RSSDataUpdating", main_window_state_, rss_data_updated_state_);
    transitions_.addTransition("RSSDataUpdated", rss_data_updated_state_, main_window_state_);
    transitions_.addTransition("StartOptionWindow", main_window_state_, option_window_state_);
    transitions_.addTransition("UpdatingSettings", option_window_state_, update_settings_state_);
    transitions_.addTransition("SettingsUpdated", update_settings_state_, main_window_state_);
}

JelayzkaStateMachine::~JelayzkaStateMachine ()
{

}

void JelayzkaStateMachine::onStateChanged (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__<<": event: "<<event;
    transitions_.makeTransition(current_state_, event);
}

