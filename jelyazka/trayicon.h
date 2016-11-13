#ifndef TRAYICON_H
#define TRAYICON_H


#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

#include "viewwindow.h"
#include "about.h"


class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = 0);
    ~TrayIcon();

private:
    QSystemTrayIcon *tray_icon_;
    QMenu *tray_icon_menu_;
    QAction *about_;
    QAction *close_;
    QAction *view_;
    ViewWindow *view_window_;
    About *about_gui_;

    void createActions();
    void createTrayIcon();
    void setIcon();
    void closeEvent(QCloseEvent *); // Overriding the window's close event

private slots:
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void viewWindow();
    void showAbout();
};

#endif // TRAYICON_H
