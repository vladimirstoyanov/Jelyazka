#include "jelyazkamanager.h"

JelyazkaManager::JelyazkaManager():
    init_window_                (std::make_shared<InitWindow> ())
    , jelyazka_state_machine_   (std::make_shared<JelayzkaStateMachine> ())
{
}

void JelyazkaManager::makeConnections ()
{

}
