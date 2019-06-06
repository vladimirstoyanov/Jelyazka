#ifndef JELAYZKA_STATEMANAGER_H
#define JELAYZKA_STATEMANAGER_H

#include <memory>

#include <QObject>
#include <QtDebug>

#include "about_window_state.hpp"
#include "add_rss_data_state.hpp"
#include "help_window_state.hpp"
#include "idle_state.hpp"
#include "init_window_state.hpp"
#include "main_window_state.hpp"
#include "option_window_state.hpp"
#include "remove_old_data_state.hpp"
#include "rss_data_updated_state.hpp"
#include "rss_search_window_state.hpp"
#include "state.hpp"
#include "transition.hpp"
#include "tray_icon_state.hpp"
#include "update_settings_state.hpp"

class JelayzkaStateMachine: public QObject
{
     Q_OBJECT
public:
    JelayzkaStateMachine ();
    virtual ~JelayzkaStateMachine ();

public slots:
    void onAddRssData ();

    void onHideAboutWindow ();
    void onHideHelpWindow ();
    void onHideInitWindow ();
    void onHideMainWindow ();
    void onHideOptionWindow ();
    void onHideRssSearchWindow ();
    void onHideTrayIcon ();

    void onRssDataAdded ();

    void onShowAboutWindow ();
    void onShowHelpWindow ();
    void onShowInitWindow ();
    void onShowMainWindow ();
    void onShowOptionWindow ();
    void onShowRssSearchWindow ();
    void onShowTrayIcon ();

    void onStartRssRefreshData ();
    void onStopRssRefreshData ();

    void onStateChanged (const QString &event);

    void onUpdateSettings ();
    void onUpdateRssData ();

signals:
    void addRssData ();

    void hideAboutWindow();
    void hideHelpWindow();
    void hideInitWindow();
    void hideMainWindow();
    void hideOptionWindow();
    void hideRssSearchWindow();
    void hideTrayIcon();

    void rssDataAdded ();

    void showAboutWindow();
    void showHelpWindow();
    void showInitWindow();
    void showMainWindow();
    void showOptionWindow();
    void showRssSearchWindow();
    void showTrayIcon();

    void startRssRefreshData ();
    void settingsUpdated     ();
    void stopRssRefreshData  ();

    void updateRssData();
    void updateSettings ();


private:
    std::shared_ptr<AboutWindowState>       about_window_state_;
    std::shared_ptr<AddRssDataState>        add_rss_data_state_;
    std::shared_ptr<Jelyazka::IState>       current_state_;
    std::shared_ptr<HelpWindowState>        help_window_state_;
    std::shared_ptr<IdleState>              idle_state_;
    std::shared_ptr<InitWindowState>        init_window_state_;
    std::shared_ptr<MainWindowState>        main_window_state_;
    std::shared_ptr<OptionWindowState>      option_window_state_;
    std::shared_ptr<RemoveOldDataState>     remove_old_data_state_;
    std::shared_ptr<RssDataUpdatedState>    rss_data_updated_state_;
    std::shared_ptr<RssSearchWindowState>   rss_search_window_state_;
    Transition                              transitions_;
    std::shared_ptr<TrayIconState>          tray_icon_state_;
    std::shared_ptr<UpdateSettingsState>    update_settings_state_;

private:
    void hideWindowConnections ();
    void makeConnections ();
    void showWindowConnections ();
};

#endif
