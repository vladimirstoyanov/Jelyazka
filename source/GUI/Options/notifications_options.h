#ifndef NOTIFICATIONOPTIONS_H
#define NOTIFICATIONOPTIONS_H

#include <memory>
#include <vector>

#include <QApplication>

#include "options.h"
#include "ui_optionswindow.h"

namespace Ui
{
    class OptionsWindow;
}

class NotificationsOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    explicit NotificationsOptions();

    virtual ~NotificationsOptions() = default;

    virtual void setupGui ();
    virtual void show ();
    virtual void hide ();
};
#endif // NOTIFICATIONOPTIONS_H
