#ifndef TRAYICON_H
#define TRAYICON_H

#include <memory>

#include <QApplication>
#include <QCloseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

#include "GUI/about_window.h"
#include "settings.h"

class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = nullptr);
    virtual ~TrayIcon();

    void addIcon(); //ToDo: move this method to the private section

private slots:
    void mainWindow();
    void showAbout();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void quitApplication();

private:
    std::shared_ptr<QAction>         about_;
    std::shared_ptr<About>           about_window_;
    std::shared_ptr<QAction>         close_;
    std::shared_ptr<QAction>         main_;
    std::shared_ptr<QSystemTrayIcon> tray_icon_;
    std::shared_ptr<QMenu>           tray_icon_menu_;

    void closeEvent(QCloseEvent *);
    void makeActionsConnection();
    void createTrayIcon();
    void setIcon();

signals:
   void stateChanged (const QString &);
};

#endif // TRAYICON_H
