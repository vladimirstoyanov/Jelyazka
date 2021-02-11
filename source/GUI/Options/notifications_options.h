#ifndef NOTIFICATIONSOPTIONS_H
#define NOTIFICATIONSOPTIONS_H

#include <memory>
#include <vector>

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QListWidget>
#include <QSpinBox>
#include <QTextEdit>

#include "options.h"
#include "settings.h"

class NotificationsOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    NotificationsOptions(QWidget *parent, const int tree_widget_width, const int ok_button_height);

    virtual ~NotificationsOptions();

    void initilize () override;
    void loadSettings () override;
    void hide () override;
    void resize () override;
    void saveSettings () override;
    void setupGui () override;
    void show () override;

private slots:
    void on_cb_enable_notification(bool enabled);

private:
    std::shared_ptr<QCheckBox>              cb_enable_notification_;
    std::shared_ptr<QLabel>                 l_refresh_time_;
    std::shared_ptr<QSpinBox>               sb_refresh_time_;

private:
     int                                     ok_button_height_;
     int                                     tree_widget_width_;
     QWidget *                               parent;
};
#endif // NOTIFICATIONSOPTIONS_H
