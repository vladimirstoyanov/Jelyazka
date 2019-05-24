#ifndef TRAYICON_H
#define TRAYICON_H

#include <memory>

#include <QApplication>
#include <QCloseEvent>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

class TrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent = nullptr);
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
    std::shared_ptr<QSystemTrayIcon> tray_icon_;
    std::shared_ptr<QMenu> tray_icon_menu_;
    std::shared_ptr<QAction> about_;
    std::shared_ptr<QAction> close_;
    std::shared_ptr<QAction> main_;

signals:
   void stateChanged (const QString &);
};

#endif // TRAYICON_H
