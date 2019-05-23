#include "jelyazka_state_machine.hpp"

JelayzkaStateMachine::JelayzkaStateMachine ():
    current_state_              (std::make_shared<IdleState> ())
    , help_window_state_        (std::make_shared<HelpWindowState> ())
    , idle_state_               (std::make_shared<IdleState> ())
    , init_window_state_        (std::make_shared<InitWindowState> ())
    , main_window_state_        (std::make_shared<MainWindowState> ())
    , option_window_state_      (std::make_shared<OptionWindowState> ())
    , remove_old_data_state_    (std::make_shared<RemoveOldDataState> ())
    , rss_data_updated_state_   (std::make_shared<RssDataUpdatedState> ())
    , rss_search_window_state_  (std::make_shared<RssSearchWindowState> ())
    , transitions_              ()
    , update_settings_state_    (std::make_shared<UpdateSettingsState> ())
{
    //ToDo: add transitions
    transitions_.addTransition("RemoveOldData", idle_state_, remove_old_data_state_);
    transitions_.addTransition("RemoveOldDataFinished", remove_old_data_state_, init_window_state_);
    transitions_.addTransition("RSSDataDownloaded", init_window_state_, main_window_state_);
    transitions_.addTransition("RSSDataUpdating", main_window_state_, rss_data_updated_state_);
    transitions_.addTransition("RSSDataUpdated", rss_data_updated_state_, main_window_state_);

    transitions_.addTransition("ShowOptionWindow"   , main_window_state_, option_window_state_);
    transitions_.addTransition("ShowHelpWindow"     , main_window_state_, help_window_state_);
    transitions_.addTransition("ShowRssSearchWindow", main_window_state_, rss_search_window_state_);

    transitions_.addTransition("UpdatingSettings", option_window_state_, update_settings_state_);
    transitions_.addTransition("HideOptionWindow", option_window_state_, main_window_state_);

    transitions_.addTransition("SettingsUpdated", update_settings_state_, main_window_state_);

    transitions_.addTransition("HideRssSearchWindow", rss_search_window_state_, main_window_state_);

    transitions_.addTransition("HideHelpWindow"     , help_window_state_, main_window_state_);

    makeConnections();
}

JelayzkaStateMachine::~JelayzkaStateMachine ()
{

}

void JelayzkaStateMachine::onStateChanged (const QString &event)
{
    qDebug()<<__PRETTY_FUNCTION__<<": event: "<<event;
    transitions_.makeTransition(current_state_, event);
}

void JelayzkaStateMachine::makeConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    //transition to remove old data state
    connect( remove_old_data_state_.get()
            , SIGNAL(removeOldDataFinished(const QString &))
            , this
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //show connections
    //show option window
    connect( option_window_state_.get()
            , SIGNAL(showOptionWindow())
            , this
            , SLOT(onShowOptionWindow())
            , Qt::QueuedConnection);

    //show init window
    connect( init_window_state_.get()
            , SIGNAL(showInitWindow())
            , this
            , SLOT(onShowInitWindow())
            , Qt::QueuedConnection);

    //show main window
    connect( main_window_state_.get()
            , SIGNAL(showMainWindow())
            , this
            , SLOT(onShowMainWindow())
            , Qt::QueuedConnection);


    //show help window
    connect( help_window_state_.get()
            , SIGNAL(showHelpWindow())
            , this
            , SLOT(onShowHelpWindow())
            , Qt::QueuedConnection);

    //show rss search window
    connect( rss_search_window_state_.get()
            , SIGNAL(showRssSearchWindow())
            , this
            , SLOT(onShowRssSearchWindow())
            , Qt::QueuedConnection);
}

void JelayzkaStateMachine::onShowInitWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showInitWindow());
}

void JelayzkaStateMachine::onShowMainWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showMainWindow());
}

void JelayzkaStateMachine::onShowOptionWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showOptionWindow());
}

void JelayzkaStateMachine::onShowHelpWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showHelpWindow());
}

void JelayzkaStateMachine::onShowRssSearchWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showRssSearchWindow());
}

