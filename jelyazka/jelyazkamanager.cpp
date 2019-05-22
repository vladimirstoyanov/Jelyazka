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
}

void JelyazkaManager::makeConnections ()
{
    //use observer pattern
}
