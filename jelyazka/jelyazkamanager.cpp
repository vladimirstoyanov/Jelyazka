#include "jelyazkamanager.h"

JelyazkaManager::JelyazkaManager():
    help_window_ (std::make_shared<Help> ())
    , init_window_ (std::make_shared<InitWindow> ())
    , main_window_ (std::make_shared<MainWindow> ())
    , notification_window_ (std::make_shared<NotificationWindow> ())
    , jelyazka_state_machine_(std::make_shared<JelayzkaStateMachine> ())
    , option_window_ (std::make_shared<OptionsWindow> ())
    , rss_search_window_(std::make_shared<RSSSearchGUI> ())
    , tray_icon_(std::make_shared<TrayIcon> ())
{
    //main_window_->show();
    //init_window_->show();
    //notification_window_->show(); //FIXME It seems that doesn't
    //rss_search_window_->show();
    //tray_icon_->show(); //FIXME: the tray icon desn't appear. An empty window appears instead.
    //option_window_->show();
    makeConnections();
    emit (removeOldData("RemoveOldData"));
}
/*
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
    */
void JelyazkaManager::makeConnections ()
{
    //transition to "remove old data" state
    connect( this
            , SIGNAL(removeOldData(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //transition to "main window" state
    connect( init_window_.get()
            , SIGNAL(rssDataDownloaded(const QString &)) //
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //show window connections
    //show OptionWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showOptionWindow())
            , this
            , SLOT(onShowOptionWindow())
            , Qt::QueuedConnection);

    connect( main_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , this
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //show InitWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showInitWindow())
            , this
            , SLOT(onShowInitWindow())
            , Qt::QueuedConnection);

    //show MainWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showMainWindow())
            , this
            , SLOT(onShowMainWindow())
            , Qt::QueuedConnection);

    //hide window connections
    //hide option window
    connect( this
            , SIGNAL(hideOptionWindow())
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //hide help window
    connect( this
            , SIGNAL(hideHelpWindow())
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //hide rss search window
    connect( this
            , SIGNAL(hideRssSearchWindow())
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);
}


void JelyazkaManager::onShowOptionWindow ()
{
   qDebug()<<__PRETTY_FUNCTION__;
   option_window_->show();
}

void JelyazkaManager::onShowInitWindow ()
{
   qDebug()<<__PRETTY_FUNCTION__;
   init_window_->show();
}

void JelyazkaManager::onShowMainWindow ()
{
   qDebug()<<__PRETTY_FUNCTION__;
   main_window_->show();
}
