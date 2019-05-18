#include "trayicon.h"

TrayIcon::TrayIcon(QWidget *parent, std::shared_ptr<MainWindow> main_window_)
    : QWidget(parent),
      main_window_(main_window_),
      about_gui_(std::make_shared<About>())
{
    createActions();
    createTrayIcon();
    setIcon();
}

TrayIcon::~TrayIcon()
{
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
    main_ =std::make_shared<QAction>(tr("&Open Jelyazka"), this);
    connect(main_.get(), SIGNAL(triggered()), this, SLOT(mainWindow()));

    about_ = std::make_shared<QAction>(tr("&About"), this);
    connect(about_.get(), SIGNAL(triggered()), this, SLOT(showAbout()));

    close_ = std::make_shared<QAction>(tr("&Quit"), this);
    connect(close_.get(), SIGNAL(triggered()), qApp, SLOT(quit()));
}
void TrayIcon::createTrayIcon()
{
    tray_icon_menu_ = std::make_shared<QMenu>(this);

    tray_icon_menu_->addAction(main_.get());
    tray_icon_menu_->addSeparator();
    tray_icon_menu_->addAction(about_.get());
    tray_icon_menu_->addSeparator();
    tray_icon_menu_->addAction(close_.get());


    tray_icon_ = std::make_shared<QSystemTrayIcon>(this);
    tray_icon_->setContextMenu(tray_icon_menu_.get());


    connect(
            tray_icon_.get(),
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
