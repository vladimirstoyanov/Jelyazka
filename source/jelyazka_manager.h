#ifndef JELYAZKAMANAGER_H
#define JELYAZKAMANAGER_H

#include <memory>

#include <QObject>
#include <QtDebug>

#include "GUI/about_window.h"
#include "GUI/help_window.h"
#include "GUI/init_window.h"
#include "GUI/main_window.h"
#include "GUI/notification_window.h"
#include "GUI/Options/options_window.h"
#include "GUI/rss_search_window.h"
#include "GUI/tray_icon.h"
#include "JelayzkaStateMachine/jelyazka_state_machine.hpp"
#include "settings.h"
#include "RSS/refresh_rss_data.h"
#include "RSS/update_rss_data.h"

class JelyazkaManager: public QObject
{
        Q_OBJECT
public:
    JelyazkaManager();
    virtual ~JelyazkaManager () = default;

    void makeConnections ();

public slots:
    void onHideAboutWindow      ();
    void onHideHelpWindow       ();
    void onHideInitWindow       ();
    void onHideMainWindow       ();
    void onHideOptionWindow     ();
    void onHideRssSearchWindow  ();
    void onHideTrayIcon         ();

    void onShowAboutWindow      ();
    void onShowHelpWindow       ();
    void onShowInitWindow       ();
    void onShowMainWindow       ();
    void onShowOptionWindow     ();
    void onShowRssSearchWindow  ();
    void onShowTrayIcon         ();

    void onUpdateSettings       ();

private:
    std::shared_ptr<About>                  about_window_;
    std::shared_ptr<Help>                   help_window_;
    std::shared_ptr<InitWindow>             init_window_;
    std::shared_ptr<MainWindow>             main_window_;
    std::shared_ptr<NotificationWindow>     notification_window_;
    std::shared_ptr<JelayzkaStateMachine>   jelyazka_state_machine_;
    std::shared_ptr<OptionsWindow>          option_window_;
    std::shared_ptr<RefreshRssData>         refresh_rss_data_;
    std::shared_ptr<RSSSearchGUI>           rss_search_window_;
    std::shared_ptr<TrayIcon>               tray_icon_;
    std::shared_ptr<UpdateRssData>          update_rss_data_;

    void connectionsFromJelyazkaStateMachine ();
    void connectionsToJelyazkaStateMachine ();

signals:
    void stateChanged           (const QString &);
    void startRssRefreshData    ();
    void stopRssRefreshData     ();
};

#endif // JELYAZKAMANAGER_H
