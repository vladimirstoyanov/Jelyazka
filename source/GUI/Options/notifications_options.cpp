#include "GUI/Options/notifications_options.h"

NotificationsOptions::NotificationsOptions(QWidget *parent, const int tree_widget_width, const int ok_button_height):
    cb_enable_notification_(std::make_shared<QCheckBox>(parent))
    , l_refresh_time_ (std::make_shared<QLabel>(parent))
    , sb_refresh_time_ (std::make_shared<QSpinBox> (parent))
    , ok_button_height_ (ok_button_height)
    , tree_widget_width_ (tree_widget_width)
    , parent_ (parent)
{


}

NotificationsOptions::~NotificationsOptions()
{

}

void NotificationsOptions::resize()
{

}

void NotificationsOptions::saveSettings ()
{
    Jelyazka::Settings::setRefreshFeedsTime(sb_refresh_time_->value());
    Jelyazka::Settings::setIsNotificationsEnabled(cb_enable_notification_->isChecked());
}

void NotificationsOptions::loadSettings ()
{
    sb_refresh_time_->setValue(Jelyazka::Settings::getRefreshFeedsTime());
    cb_enable_notification_->setChecked(Jelyazka::Settings::getIsNotificationsEnabled());
    on_cb_enable_notification (Jelyazka::Settings::getIsNotificationsEnabled());
}

void NotificationsOptions::setupGui ()
{
    //notification widgets
    l_refresh_time_->setGeometry(tree_widget_width_ + 10,
                                 5,
                                 l_refresh_time_->width()+50,
                                 l_refresh_time_->height());

    l_refresh_time_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    l_refresh_time_->setWordWrap(true);
    l_refresh_time_->setText("Refresh feeds time (minutes):");


    sb_refresh_time_->setGeometry(tree_widget_width_  + 10,
                                  l_refresh_time_->y()+l_refresh_time_->height() + 5,
                                  sb_refresh_time_->width(),
                                  sb_refresh_time_->height());
    sb_refresh_time_->setMinimum(1);
    sb_refresh_time_->setMaximum(60);

    cb_enable_notification_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    cb_enable_notification_->setGeometry(tree_widget_width_  + 10,sb_refresh_time_->y() + sb_refresh_time_->height() + 5,
                                         cb_enable_notification_->width()+100,
                                         cb_enable_notification_->height());

    cb_enable_notification_->setText("Enable notification window");
    cb_enable_notification_->setChecked(true);

    connect(cb_enable_notification_.get(),
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_cb_enable_notification(bool)));
    hide();
}

void NotificationsOptions::show ()
{
    sb_refresh_time_->show();
    l_refresh_time_->show();
    cb_enable_notification_->show();
}
void NotificationsOptions::hide ()
{
    sb_refresh_time_->hide();
    l_refresh_time_->hide();
    cb_enable_notification_->hide();
}

void NotificationsOptions::on_cb_enable_notification(bool enabled)
{
    sb_refresh_time_->setEnabled(enabled);
    l_refresh_time_->setEnabled(enabled);
}

void NotificationsOptions::initilize ()
{

}
