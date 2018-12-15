#ifndef TRAYICON_H
#define TRAYICON_H

#include <QCloseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

#include "about.h"
#include "mainwindow.h"

class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = 0,  MainWindow *main_window_=0);
    virtual ~TrayIcon();

    void addIcon();

private slots:
    void mainWindow();
    void showAbout();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);

private:
    void closeEvent(QCloseEvent *);

private:
    void createActions();
    void createTrayIcon();
    void setIcon();

private:
    QSystemTrayIcon *tray_icon_;
    QMenu *tray_icon_menu_;
    QAction *about_;
    QAction *close_;
    QAction *main_;
    MainWindow *main_window_;
    About *about_gui_;
};

#endif // TRAYICON_H
