#include "jelyazkamanager.h"

JelyazkaManager::JelyazkaManager():
    init_window_                (std::make_shared<InitWindow> ())
    , jelyazka_state_machine_   (std::make_shared<JelayzkaStateMachine> ())
    , main_window_ (std::make_shared<MainWindow> ())
{
    main_window_->show();
    makeConnections();
}

void JelyazkaManager::makeConnections ()
{
    //use observer pattern
}
