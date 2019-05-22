#ifndef JELYAZKAMANAGER_H
#define JELYAZKAMANAGER_H

#include <memory>

#include <QObject>

#include "about.h"
#include "help.h"
#include "InitWindow/initwindow.h"
#include "JelayzkaStateMachine/jelyazka_state_machine.hpp"
#include "mainwindow.h"
#include "notificationwindow.h"
#include "Options/optionswindow.h"
#include "rsssearchgui.h"
#include "trayicon.h"

class JelyazkaManager
{
        //Q_OBJECT
public:
    JelyazkaManager();

    void makeConnections ();

private:
    std::shared_ptr<About>      about_window_;
    std::shared_ptr<Help>       help_window_;
    std::shared_ptr<InitWindow> init_window_;
    std::shared_ptr<MainWindow> main_window_;
    std::shared_ptr<NotificationWindow> notification_window_;
    std::shared_ptr<JelayzkaStateMachine> jelyazka_state_machine_;
    std::shared_ptr<OptionsWindow> option_window_;
    std::shared_ptr<RSSSearchGUI> rss_search_window_;
    std::shared_ptr<TrayIcon> tray_icon_;

signals:
       //void transitToInitWindow(const QString);

};

#endif // JELYAZKAMANAGER_H
