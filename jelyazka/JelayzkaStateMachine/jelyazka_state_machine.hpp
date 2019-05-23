#ifndef JELAYZKA_STATEMANAGER_H
#define JELAYZKA_STATEMANAGER_H

#include <memory>

#include <QObject>
#include <QtDebug>

#include "idle_state.hpp"
#include "init_window_state.hpp"
#include "main_window_state.hpp"
#include "option_window_state.hpp"
#include "remove_old_data_state.hpp"
#include "rss_data_updated_state.hpp"
#include "state.hpp"
#include "transition.hpp"
#include "update_settings_state.hpp"

//ToDo: add transitions

class JelayzkaStateMachine: public QObject
{
     Q_OBJECT
public:
    JelayzkaStateMachine ();
    virtual ~JelayzkaStateMachine ();

public slots:
    void onStateChanged (const QString &event);

private:
    std::shared_ptr<Jelyazka::IState>       current_state_;
    std::shared_ptr<IdleState>              idle_state_;
    std::shared_ptr<InitWindowState>        init_window_state_;
    std::shared_ptr<MainWindowState>        main_window_state_;
    std::shared_ptr<OptionWindowState>      option_window_state_;
    std::shared_ptr<RemoveOldDataState>     remove_old_data_state_;
    std::shared_ptr<RssDataUpdatedState>    rss_data_updated_state_;
    Transition                              transitions_;
    std::shared_ptr<UpdateSettingsState>    update_settings_state_;

private:
    void makeConnections ();

};

#endif
