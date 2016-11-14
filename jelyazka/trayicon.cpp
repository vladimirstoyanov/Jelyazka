#include "trayicon.h"

TrayIcon::TrayIcon(QWidget *parent, MainWindow *main_window_)
    : QWidget(parent),
      main_window_(main_window_),
      about_gui_(new About())
{
    createActions();
    createTrayIcon();
    setIcon();
}

TrayIcon::~TrayIcon()
{
    if (tray_icon_!=NULL)
        delete tray_icon_;
    if (tray_icon_menu_!=NULL)
        delete tray_icon_menu_;
    if (about_!=NULL)
        delete about_;
    if (close_!=NULL)
        delete close_;
    if (main_!=NULL)
        delete main_;
    if (main_window_!=NULL)
        delete main_window_;

    delete about_gui_;
}

void TrayIcon::addIcon()
{
    tray_icon_->show();
}

void TrayIcon::mainWindow()
{
    main_window_->show();
}

void TrayIcon::showAbout()
{
    about_gui_->show();
}

void TrayIcon::createActions()
{
    main_ = new QAction(tr("&Open Jelyazka"), this);
    connect(main_, SIGNAL(triggered()), this, SLOT(mainWindow()));

    about_ = new QAction(tr("&About"), this);
    connect(about_, SIGNAL(triggered()), this, SLOT(showAbout()));

    close_ = new QAction(tr("&Quit"), this);
    connect(close_, SIGNAL(triggered()), qApp, SLOT(quit()));
}
void TrayIcon::createTrayIcon()
{
    tray_icon_menu_ = new QMenu(this);

    tray_icon_menu_->addAction(main_);
    tray_icon_menu_->addSeparator();
    tray_icon_menu_->addAction(about_);
    tray_icon_menu_->addSeparator();
    tray_icon_menu_->addAction(close_);


    tray_icon_ = new QSystemTrayIcon(this);
    tray_icon_->setContextMenu(tray_icon_menu_);


    connect(
            tray_icon_,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
}

void TrayIcon::setIcon()
{
    tray_icon_->setIcon(QIcon("../resources/Jelyazka_icon.png"));
}

void TrayIcon::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
        main_window_->show();
}

void TrayIcon::closeEvent(QCloseEvent *event)
{
    if (tray_icon_->isVisible()) {
        tray_icon_->showMessage(tr("Still here!!!"),
        tr("This application is still running. To quit please click this icon and select Quit"));
        hide();


        event->ignore(); // Don't let the event propagate to the base class
    }
}
