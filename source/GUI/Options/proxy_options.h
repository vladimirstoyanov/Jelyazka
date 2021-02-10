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

class ProxyOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    explicit ProxyOptions(){}

    virtual ~ProxyOptions() = default;

    virtual void setupGui ();
    virtual void show ();
    virtual void hide ();
};
#endif // NOTIFICATIONOPTIONS_H
