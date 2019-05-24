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
    makeConnections();
    emit (stateChanged("RemoveOldData"));
}
void JelyazkaManager::makeConnections ()
{
    connectionsFromJelyazkaStateMachine();
    connectionsToJelyazkaStateMachine();
}

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
}

void JelyazkaManager::connectionsFromJelyazkaStateMachine ()
{
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
            , SLOT(onHideMainWindow())
            , Qt::QueuedConnection);

    //hide help window
    connect( jelyazka_state_machine_.get()
            , SIGNAL(hideHelpWindow())
            , this
            , SLOT(onHideHelpWindow())
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
