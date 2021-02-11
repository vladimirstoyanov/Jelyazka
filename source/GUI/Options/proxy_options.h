#ifndef PROXYOPTIONS_H
#define PROXYOPTIONS_H

#include <memory>
#include <vector>

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>

#include "database.h"
#include "options.h"
#include "settings.h"
#include "ui_optionswindow.h"

namespace Ui
{
    class OptionsWindow;
}

class ProxyOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    ProxyOptions(QWidget *parent, const int tree_widget_width, const int ok_button_high);

    virtual ~ProxyOptions();

    virtual void initilize ();
    virtual void resize ();
    virtual void saveSettings ();
    virtual void loadSettings ();
    virtual void setupGui ();
    virtual void show ();
    virtual void hide ();

private slots:
     void on_cb_enable_proxy_clicked(bool state);
private:
    std::shared_ptr<QCheckBox>              cb_enable_proxy_;
    std::shared_ptr<QLabel>                 l_proxy_url_;
    std::shared_ptr<QLabel>                 l_proxy_port_;
    std::shared_ptr<QTextEdit>              te_proxy_url_;
    std::shared_ptr<QTextEdit>              te_proxy_port_;

private:
     DataBase                                data_base_;
     int                                     ok_button_high_;
     int                                     tree_widget_width_;
     QWidget *                               parent;
};
#endif // PROXYOPTIONS_H
