#ifndef JELYAZKAMANAGER_H
#define JELYAZKAMANAGER_H

#include <memory>

#include <QObject>

#include "InitWindow/initwindow.h"
#include "JelayzkaStateMachine/jelyazka_state_machine.hpp"
#include "mainwindow.h"

class JelyazkaManager
{
        //Q_OBJECT
public:
    JelyazkaManager();

    void makeConnections ();

private:
    std::shared_ptr<InitWindow> init_window_;
    std::shared_ptr<MainWindow> main_window_;
    std::shared_ptr<JelayzkaStateMachine> jelyazka_state_machine_;
    //std::shared_ptr<MainWindow> main_window_;

signals:
       //void transitToInitWindow(const QString);

};

#endif // JELYAZKAMANAGER_H
