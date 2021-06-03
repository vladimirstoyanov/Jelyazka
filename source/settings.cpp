#include "settings.h"
#include <QMessageBox>

namespace Jelyazka
{
const QString        Settings::filename_ = "../resources/Options";
bool                 Settings::is_filtering_enabled_ = false;
bool                 Settings::is_notifications_enabled_ = false;
bool                 Settings::is_proxy_connection_enabled_ = false;
QString              Settings::proxy_ip_address_ = "";
QString              Settings::proxy_port_ = "";
unsigned int         Settings::refresh_feeds_time_ = 1;

Settings::Settings()
{

}

Settings::~Settings ()
{
}

void Settings::setProxySettings ()
{
    if (Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        QString proxyAddr = Jelyazka::Settings::getProxyIpAddress();
        proxy.setHostName(proxyAddr);
        QString port = Jelyazka::Settings::getProxyPort();
        proxy.setPort(port.toInt());
        QNetworkProxy::setApplicationProxy(proxy);
    }
    else if (!Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        QNetworkProxy::setApplicationProxy(QNetworkProxy(QNetworkProxy::DefaultProxy));
    }
}

int Settings::loadRefreshTime (QTextStream &textStream)
{
    QString refreshTime = "";
    QString line = textStream.readLine();

    int expected_length = 14;
    if (!isSettingsDataValid(expected_length, line, "It can't read settings data about RSS refresh time!"))
    {
        return false;
    }

    int i=expected_length;
    while (line[i] != '\n' && i<line.length())
    {
        refreshTime+=line[i];
        ++i;
    }

    return refreshTime.toInt();
}

bool Settings::loadNotificationsCheckBoxData(QTextStream & textStream)
{

    QString line = textStream.readLine();

    int expected_length = 21;
    if (!isSettingsDataValid(expected_length, line, "It can't read settings data about notification window check box!"))
    {
        return false;
    }

    if (line[expected_length]=='1')
    {
        return true;
    }

    return false;
}

bool Settings::loadProxyCheckBoxData(QTextStream & textStream)
{
    QString line = textStream.readLine();
    int expected_length = 15;
    if (!isSettingsDataValid(expected_length, line, "It can't read settings data about proxy connection check box!"))
    {
        return false;
    }

    if (line[expected_length] == '1')
    {
        return true;
    }

    return false;
}

QString Settings::loadProxyServerAddress (QTextStream & textStream)
{
    QString line = textStream.readLine();
    int expected_length = 15;
    if (!isSettingsDataValid (expected_length, line, "It can't read settings data about proxy server address!"))
    {
        return "";
    }

    return extractLineData(expected_length, line);
}

QString Settings::loadProxyPort (QTextStream & textStream)
{
    QString line = textStream.readLine();
    int expected_length = 12;
    if (!isSettingsDataValid (expected_length, line, "It can't read settings data about proxy port!"))
    {
        return "";
    }

    return extractLineData(expected_length, line);
}

QString Settings::extractLineData (int index, const QString &line)
{
    QString result ="";
    while(index<line.length() && line[index]!='\n')
    {
        result+=line[index];
        ++index;
    }
    return result;
}

bool Settings::isSettingsDataValid (const int expected_length,
                          const QString &line,
                          const QString &error_message)
{
    if (line.length()>=expected_length && line[expected_length-1] == ' ')
    {
        return true;
    }

    QMessageBox::critical(0, "Error!", error_message);
    return false;
}

bool Settings::loadFiltersCheckBoxData (QTextStream &textStream)
{
    QString line = textStream.readLine();
    int expected_length = 17;
    if (!isSettingsDataValid (expected_length, line, "It can't read settings data about filters check box!"))
    {
        return false;
    }

    if (line[expected_length] == '1')
    {
        return true;
    }

    return false;
}

void Settings::loadSettings()
{
    QFile file(filename_);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, "Error!", "Can't read \'Options\' file: " + file.errorString());
        return;
    }

    QTextStream in(&file);

    refresh_feeds_time_ = loadRefreshTime(in);
    is_notifications_enabled_ = loadNotificationsCheckBoxData(in);
    is_proxy_connection_enabled_ = loadProxyCheckBoxData(in);
    proxy_ip_address_ = loadProxyServerAddress(in);
    proxy_port_ = loadProxyPort (in);
    is_filtering_enabled_ = loadFiltersCheckBoxData(in);

    file.close();
    setProxySettings ();
}

void Settings::saveNotificationsSettings (QTextStream & out)
{
    out << "Refresh time: " << refresh_feeds_time_ <<'\n';
    if (is_notifications_enabled_)
    {
        out << "Notification window: 1\n";
    }
    else
    {
        out << "Notification window: 0\n";
    }
}

void Settings::saveProxySettings (QTextStream & out)
{
    if (is_proxy_connection_enabled_)
    {
        out << "Enabled Proxy: 1\n";
    }
    else
    {
        out << "Enabled Proxy: 0\n";
    }

    out<<"Proxy Address: "<< proxy_ip_address_<<"\n";
    out<<"Proxy Port: "<< proxy_port_<<"\n";
}

void Settings::saveFiltersSettings (QTextStream & out)
{
    if (is_filtering_enabled_)
    {
        out << "Enabled Filters: 1\n";
    }
    else
    {
        out << "Enabled Filters: 0\n";
    }
}

void Settings::saveSettings ()
{
    QFile file(filename_);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    if(!file.isOpen())
    {
        QMessageBox::critical(0, "Error!", "Couldn't open \'Options\' file: " + file.errorString());
        return;
    }

    saveNotificationsSettings(out);
    saveProxySettings(out);
    saveFiltersSettings(out);

    file.close();
}

} //namespace Jelyazka
