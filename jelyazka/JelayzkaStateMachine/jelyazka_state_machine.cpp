#include "jelyazka_state_machine.hpp"

JelayzkaStateMachine::JelayzkaStateMachine ():
    about_window_state_         (std::make_shared<AboutWindowState> ())
    , current_state_            (std::make_shared<IdleState> ())
    , help_window_state_        (std::make_shared<HelpWindowState> ())
    , idle_state_               (std::make_shared<IdleState> ())
    , init_window_state_        (std::make_shared<InitWindowState> ())
    , main_window_state_        (std::make_shared<MainWindowState> ())
    , option_window_state_      (std::make_shared<OptionWindowState> ())
    , remove_old_data_state_    (std::make_shared<RemoveOldDataState> ())
    , rss_data_updated_state_   (std::make_shared<RssDataUpdatedState> ())
    , rss_search_window_state_  (std::make_shared<RssSearchWindowState> ())
    , transitions_              ()
    , tray_icon_state_          (std::make_shared<TrayIconState> ())
    , update_settings_state_    (std::make_shared<UpdateSettingsState> ())
{
    //ToDo: add transitions
    transitions_.addTransition("RemoveOldData"         , idle_state_, remove_old_data_state_);

    transitions_.addTransition("RemoveOldDataFinished" , remove_old_data_state_, init_window_state_);
    transitions_.addTransition("RSSDataDownloaded"     , init_window_state_, main_window_state_);
    transitions_.addTransition("RSSDataUpdating"       , main_window_state_, rss_data_updated_state_);
    transitions_.addTransition("RSSDataUpdated"        , rss_data_updated_state_, main_window_state_);

    transitions_.addTransition("ShowOptionWindow"      , main_window_state_, option_window_state_);
    transitions_.addTransition("ShowHelpWindow"        , main_window_state_, help_window_state_);
    transitions_.addTransition("ShowRssSearchWindow"   , main_window_state_, rss_search_window_state_);
    transitions_.addTransition("HideMainWindow"        , main_window_state_, tray_icon_state_);

    transitions_.addTransition("UpdatingSettings"      , option_window_state_, update_settings_state_);
    transitions_.addTransition("HideOptionWindow"      , option_window_state_, main_window_state_);

    transitions_.addTransition("SettingsUpdated"       , update_settings_state_, main_window_state_);

    transitions_.addTransition("HideRssSearchWindow"   , rss_search_window_state_, main_window_state_);

    transitions_.addTransition("HideHelpWindow"        , help_window_state_, main_window_state_);

    transitions_.addTransition("HideTrayIcon"          , tray_icon_state_, main_window_state_);
    //transitions_.addTransition("ShowAboutWindow"       , tray_icon_state_, about_window_state_);

    //transitions_.addTransition("HideAboutWindow"       , about_window_state_, tray_icon_state_);

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

    connect( init_window_state_.get()
            , SIGNAL(updateRssData())
            , this
            , SLOT(onUpdateRssData())
            , Qt::QueuedConnection);

    connect( main_window_state_.get()
            , SIGNAL(startRssRefreshData())
            , this
            , SLOT(onStartRssRefreshData())
            , Qt::QueuedConnection);

    /*
    connect( main_window_state_.get()
            , SIGNAL(stopRssRefreshData())
            , this
            , SLOT(onStopRssRefreshData())
            , Qt::QueuedConnection);
    */
    showWindowConnections();
    hideWindowConnections();

}

void JelayzkaStateMachine::showWindowConnections()
{
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

    //show tray icon
    connect( tray_icon_state_.get()
            , SIGNAL(showTrayIcon())
            , this
            , SLOT(onShowTrayIcon())
            , Qt::QueuedConnection);

    //show about window
    connect( about_window_state_.get()
            , SIGNAL(showAboutWindow())
            , this
            , SLOT(onShowAboutWindow())
            , Qt::QueuedConnection);
}

void JelayzkaStateMachine::hideWindowConnections ()
{
    //hide option window
    connect( option_window_state_.get()
            , SIGNAL(hideOptionWindow())
            , this
            , SLOT(onHideOptionWindow())
            , Qt::QueuedConnection);

    //hide init window
    connect( init_window_state_.get()
            , SIGNAL(hideInitWindow())
            , this
            , SLOT(onHideInitWindow())
            , Qt::QueuedConnection);

    //hide main window
    connect( main_window_state_.get()
            , SIGNAL(hideMainWindow())
            , this
            , SLOT(onHideMainWindow())
            , Qt::QueuedConnection);


    //hide help window
    connect( help_window_state_.get()
            , SIGNAL(hideHelpWindow())
            , this
            , SLOT(onHideHelpWindow())
            , Qt::QueuedConnection);

    //hide rss search window
    connect( rss_search_window_state_.get()
            , SIGNAL(hideRssSearchWindow())
            , this
            , SLOT(onHideRssSearchWindow())
            , Qt::QueuedConnection);

    //hide tray icon
    connect( tray_icon_state_.get()
            , SIGNAL(hideTrayIcon())
            , this
            , SLOT(onHideTrayIcon())
            , Qt::QueuedConnection);

    //hide about window
    connect( about_window_state_.get()
            , SIGNAL(hideAboutWindow())
            , this
            , SLOT(onHideAboutWindow())
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

void JelayzkaStateMachine::onShowTrayIcon ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showTrayIcon());
}

void JelayzkaStateMachine::onShowAboutWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (showAboutWindow());
}

void JelayzkaStateMachine::onHideInitWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideInitWindow());
}

void JelayzkaStateMachine::onHideMainWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideMainWindow());
}

void JelayzkaStateMachine::onHideOptionWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideOptionWindow());
}

void JelayzkaStateMachine::onHideHelpWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideHelpWindow());
}

void JelayzkaStateMachine::onHideRssSearchWindow ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideRssSearchWindow());
}

void JelayzkaStateMachine::onHideTrayIcon ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideTrayIcon());
}

void JelayzkaStateMachine::onHideAboutWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (hideAboutWindow());
}

void JelayzkaStateMachine::onUpdateRssData()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (updateRssData());
}

void JelayzkaStateMachine::onStartRssRefreshData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (startRssRefreshData());
}

void JelayzkaStateMachine::onStopRssRefreshData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (stopRssRefreshData());
}
