#ifndef TRAYICON_H
#define TRAYICON_H


#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

#include "mainwindow.h"
#include "about.h"


class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = 0,  MainWindow *main_window_=0);
    ~TrayIcon();

    void addIcon();

private:
    QSystemTrayIcon *tray_icon_;
    QMenu *tray_icon_menu_;
    QAction *about_;
    QAction *close_;
    QAction *main_;
    MainWindow *main_window_;
    About *about_gui_;

    void createActions();
    void createTrayIcon();
    void setIcon();
    void closeEvent(QCloseEvent *);

private slots:
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void mainWindow();
    void showAbout();
};

#endif // TRAYICON_H
