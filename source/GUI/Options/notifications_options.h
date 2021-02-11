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

#include "database.h"
#include "options.h"
#include "settings.h"
#include "ui_optionswindow.h"

namespace Ui
{
    class OptionsWindow;
}

class NotificationsOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    NotificationsOptions(QWidget *parent, const int tree_widget_width, const int ok_button_high);

    virtual ~NotificationsOptions();

    virtual void initilize ();
    virtual void resize ();
    virtual void saveSettings ();
    virtual void loadSettings ();
    virtual void setupGui ();
    virtual void show ();
    virtual void hide ();

private:
    std::shared_ptr<QCheckBox>              cb_enable_notification_;
    std::shared_ptr<QLabel>                 l_refresh_time_;
    std::shared_ptr<QSpinBox>               sb_refresh_time_;

private:
     DataBase                                data_base_;
     int                                     ok_button_high_;
     int                                     tree_widget_width_;
     QWidget *                               parent;
};
#endif // NOTIFICATIONSOPTIONS_H
