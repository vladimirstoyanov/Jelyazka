#include "GUI/Options/proxy_options.h"

ProxyOptions::ProxyOptions(QWidget *parent, const int tree_widget_width, const int ok_button_high):
    cb_enable_proxy_ (std::make_shared<QCheckBox>(parent))
    , l_proxy_url_ (std::make_shared<QLabel>(parent))
    , l_proxy_port_ (std::make_shared<QLabel> (parent))
    , te_proxy_url_ (std::make_shared<QTextEdit>(parent))
    , te_proxy_port_ (std::make_shared<QTextEdit>(parent))
    , ok_button_high_ (ok_button_high)
    , tree_widget_width_ (tree_widget_width)
    , parent (parent)
{

}

ProxyOptions::~ProxyOptions()
{

}

void ProxyOptions::resize()
{
}

void ProxyOptions::saveSettings ()
{
    Jelyazka::Settings::setIsProxyConnectionEnabled(cb_enable_proxy_->isChecked());
    Jelyazka::Settings::setProxyPort(te_proxy_port_->toPlainText());
    Jelyazka::Settings::setProxyIpAddress(te_proxy_url_->toPlainText());
}
void ProxyOptions::loadSettings ()
{
    if (Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        cb_enable_proxy_->setChecked(false);
        l_proxy_url_->setEnabled(false);
        l_proxy_port_->setEnabled(false);
        te_proxy_url_->setEnabled(false);
        te_proxy_port_->setEnabled(false);
    }
    else
    {
        cb_enable_proxy_->setChecked(true);
        l_proxy_url_->setEnabled(true);
        l_proxy_port_->setEnabled(true);
        te_proxy_url_->setEnabled(true);
        te_proxy_port_->setEnabled(true);
    }
    te_proxy_url_->setText(Jelyazka::Settings::getProxyIpAddress());
    te_proxy_port_->setText(Jelyazka::Settings::getProxyPort());
}

void ProxyOptions::setupGui ()
{
    //proxy options
    cb_enable_proxy_->setChecked(false);
    cb_enable_proxy_->setText("Enable proxy connection");
    connect(cb_enable_proxy_.get(), SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_proxy_clicked(bool)));
    l_proxy_url_->setText("Proxy address:");
    l_proxy_port_->setText("Proxy port:");

    cb_enable_proxy_->setGeometry(tree_widget_width_ + 10,
                                  5,
                                  cb_enable_proxy_->width()+50,
                                  cb_enable_proxy_->height());
    l_proxy_url_->setGeometry(tree_widget_width_ + 10,
                              cb_enable_proxy_->y() + cb_enable_proxy_->height()+5,
                              l_proxy_url_->width(),
                              l_proxy_url_->height());
    te_proxy_url_->setGeometry(tree_widget_width_ + 10,
                               l_proxy_url_->y() +l_proxy_url_->height() + 5,
                               te_proxy_url_->width(),
                               te_proxy_url_->height());
    l_proxy_port_->setGeometry(tree_widget_width_ + 10,
                               te_proxy_url_->y() + te_proxy_url_->height() + 5,
                               l_proxy_port_->width(),
                               l_proxy_port_->height());
    te_proxy_port_->setGeometry(tree_widget_width_ + 10,
                                l_proxy_port_->y() + l_proxy_port_->height() + 5,
                                te_proxy_port_->width(),
                                te_proxy_port_->height());

    cb_enable_proxy_->hide();
    l_proxy_url_->hide();
    l_proxy_port_->hide();
    te_proxy_url_->hide();
    te_proxy_port_->hide();

}
void ProxyOptions::show ()
{
        cb_enable_proxy_->show();
        l_proxy_url_->show();
        l_proxy_port_->show();
        te_proxy_url_->show();
        te_proxy_port_->show();
}
void ProxyOptions::hide ()
{
    cb_enable_proxy_->hide();
    l_proxy_url_->hide();
    l_proxy_port_->hide();
    te_proxy_url_->hide();
    te_proxy_port_->hide();
}

void ProxyOptions::on_cb_enable_proxy_clicked(bool state)
{
    if (state)
    {
        l_proxy_url_->setEnabled(true);
        l_proxy_port_->setEnabled(true);
        te_proxy_url_->setEnabled(true);
        te_proxy_port_->setEnabled(true);
    }
    else
    {
        l_proxy_url_->setEnabled(false);
        l_proxy_port_->setEnabled(false);
        te_proxy_url_->setEnabled(false);
        te_proxy_port_->setEnabled(false);
    }
}

void ProxyOptions::initilize ()
{

}
