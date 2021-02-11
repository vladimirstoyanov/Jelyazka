#ifndef PROXYOPTIONS_H
#define PROXYOPTIONS_H

#include <memory>

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QTextEdit>

#include "options.h"
#include "settings.h"

class ProxyOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    ProxyOptions(QWidget *parent, const int tree_widget_width, const int ok_button_high);

    virtual ~ProxyOptions();

    void initilize () override;
    void loadSettings () override;
    void hide () override;
    void resize () override;
    void saveSettings () override;
    void setupGui () override;
    void show () override;

private slots:
     void on_cb_enable_proxy_clicked(bool enabled);

private:
    std::shared_ptr<QCheckBox>              cb_enable_proxy_;
    std::shared_ptr<QLabel>                 l_proxy_url_;
    std::shared_ptr<QLabel>                 l_proxy_port_;
    std::shared_ptr<QTextEdit>              te_proxy_url_;
    std::shared_ptr<QTextEdit>              te_proxy_port_;

private:
     int                                     ok_button_height_;
     const unsigned int                      offset_between_widgets_;
     int                                     tree_widget_width_;
     QWidget *                               parent;
};
#endif // PROXYOPTIONS_H
