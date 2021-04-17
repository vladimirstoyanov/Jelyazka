#include "jelyazka_manager.h"

JelyazkaManager::JelyazkaManager():
    about_window_                   (std::make_shared<About> ())
    , help_window_                  (std::make_shared<Help> ())
    , init_window_                  (std::make_shared<InitWindow> ())
    , main_window_                  (std::make_shared<MainWindow> ())
    , notification_window_          (std::make_shared<NotificationWindow> ())
    , jelyazka_state_machine_       (std::make_shared<JelayzkaStateMachine> ())
    , option_window_                (std::make_shared<OptionsWindow> ())
    , refresh_rss_data_             (std::make_shared<RefreshRssData> ())
    , rss_search_window_            (std::make_shared<RSSSearchGUI> ())
    , settings_                     ()
    , tray_icon_                    (std::make_shared<TrayIcon> ())
    , update_rss_data_              (std::make_shared <UpdateRssData> ())
{
    tray_icon_->addIcon();

    makeConnections();

    emit (stateChanged("RemoveOldData"));
}
void JelyazkaManager::makeConnections ()
{
    connect( refresh_rss_data_.get()
            , SIGNAL(rssDataUpdated(const QString &))
            , main_window_.get()
            , SLOT(onRssDataUpdated(const QString &))
            , Qt::QueuedConnection);

    qDebug()<<"Before connection";
    connect( refresh_rss_data_.get()
            , SIGNAL(rssDataUpdated(const QString &))
            , notification_window_.get()
            , SLOT(onRssDataUpdated(const QString &))
            , Qt::QueuedConnection);


    connectionsFromJelyazkaStateMachine();
    connectionsToJelyazkaStateMachine();
}

//ToDo: split this function
void JelyazkaManager::connectionsToJelyazkaStateMachine ()
{
    //transition to "remove old data" state
    connect( this
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( init_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( main_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( help_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( rss_search_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( option_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( tray_icon_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    connect( about_window_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

    //Rss data updated by UpdateRssData class
    connect( update_rss_data_.get()
            , SIGNAL(stateChanged(const QString &))
            , jelyazka_state_machine_.get()
            , SLOT(onStateChanged(const QString &))
            , Qt::QueuedConnection);

}

//ToDo: split this function
void JelyazkaManager::connectionsFromJelyazkaStateMachine ()
{
    //update rss data in main window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(updateRssData())
            , main_window_.get()
            , SLOT(onUpdateRSSData()) //downloads the last updates and upgrades main window widgets with the new rss data
            , Qt::QueuedConnection);

    //show window connections
    //show OptionWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showOptionWindow())
            , this
            , SLOT(onShowOptionWindow())
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

    //show Rss search window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showRssSearchWindow())
            , this
            , SLOT(onShowRssSearchWindow())
            , Qt::QueuedConnection);

    //show help window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showHelpWindow())
            , this
            , SLOT(onShowHelpWindow())
            , Qt::QueuedConnection);

    //show tray icon
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showTrayIcon())
            , this
            , SLOT(onShowTrayIcon())
            , Qt::QueuedConnection);

    //show about window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(showAboutWindow())
            , this
            , SLOT(onShowAboutWindow())
            , Qt::QueuedConnection);

    //hide OptionWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideOptionWindow())
            , this
            , SLOT(onHideOptionWindow())
            , Qt::QueuedConnection);

    //hide InitWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideInitWindow())
            , this
            , SLOT(onHideInitWindow())
            , Qt::QueuedConnection);

    //hide MainWindow
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideMainWindow())
            , this
            , SLOT(onHideMainWindow())
            , Qt::QueuedConnection);

    //hide Rss search window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideRssSearchWindow())
            , this
            , SLOT(onHideRssSearchWindow())
            , Qt::QueuedConnection);

    //hide help window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideHelpWindow())
            , this
            , SLOT(onHideHelpWindow())
            , Qt::QueuedConnection);

    //hide tray icon
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideTrayIcon())
            , this
            , SLOT(onHideTrayIcon())
            , Qt::QueuedConnection);

    //hide about window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideAboutWindow())
            , this
            , SLOT(onHideAboutWindow())
            , Qt::QueuedConnection);

    //start rss thread
    connect( jelyazka_state_machine_.get()
            , SIGNAL(startRssRefreshData())
            , refresh_rss_data_.get()
            , SLOT(onStartRssRefreshData())
            , Qt::QueuedConnection);

    //stop rss thread
    connect( jelyazka_state_machine_.get()
            , SIGNAL(stopRssRefreshData())
            , refresh_rss_data_.get()
            , SLOT(onStopRssRefreshData())
            , Qt::QueuedConnection);

    //request to update the current settings
    connect( jelyazka_state_machine_.get()
            , SIGNAL(updateSettings())
            , update_rss_data_.get()
            , SLOT(onUpdateSettings())
            , Qt::QueuedConnection);

    //settings has been updated
    connect( jelyazka_state_machine_.get()
            , SIGNAL(settingsUpdated())
            , main_window_.get()
            , SLOT(onUpdateRSSData())
            , Qt::QueuedConnection);

    //request to add new rss data
    connect( jelyazka_state_machine_.get()
            , SIGNAL(addRssData())
            , update_rss_data_.get()
            , SLOT(onAddRssData())
            , Qt::QueuedConnection);

    //rss data has been added
    connect( jelyazka_state_machine_.get()
            , SIGNAL(rssDataAdded())
            , main_window_.get()
            , SLOT(onUpdateRSSData())
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

void JelyazkaManager::onShowHelpWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    help_window_->show();
}

void JelyazkaManager::onShowRssSearchWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    rss_search_window_->show();
}

void JelyazkaManager::onShowTrayIcon()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void JelyazkaManager::onShowAboutWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    about_window_->show();
}

void JelyazkaManager::onHideOptionWindow ()
{
   qDebug()<<__PRETTY_FUNCTION__;
   option_window_->hide();
}

void JelyazkaManager::onHideInitWindow ()
{
   qDebug()<<__PRETTY_FUNCTION__;
   init_window_->hide();
}

void JelyazkaManager::onHideMainWindow ()
{
   qDebug()<<__PRETTY_FUNCTION__;
   main_window_->hide();
}

void JelyazkaManager::onHideHelpWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    help_window_->hide();
}
void JelyazkaManager::onHideRssSearchWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    rss_search_window_->hide();
}

void JelyazkaManager::onHideTrayIcon()
{
    qDebug()<<__PRETTY_FUNCTION__;
    //tray_icon_->hide();
}

void JelyazkaManager::onHideAboutWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;
    about_window_->hide();
}


void JelyazkaManager::onUpdateSettings ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}
