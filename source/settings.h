#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QNetworkProxy>

namespace Jelyazka
{

class Settings
{
public:
    //get methods
    static bool getIsNotificationsEnabled ()
    {
        return is_notifications_enabled_;
    }

    static unsigned int getRefreshFeedsTime ()
    {
        return refresh_feeds_time_;
    }

    static bool getIsProxyConnectionEnabled()
    {
        return is_proxy_connection_enabled_;
    }

    static QString getProxyIpAddress ()
    {
        return proxy_ip_address_;
    }

    static QString getProxyPort ()
    {
        return proxy_port_;
    }

    static bool getIsFilteringEnabled ()
    {
        return is_filtering_enabled_;
    }

    static void setIsNotificationsEnabled (const bool is_notifications_enabled)
    {
        is_notifications_enabled_ = is_notifications_enabled;
    }

    static void setRefreshFeedsTime (const unsigned int refresh_feeds_time)
    {
        Settings::refresh_feeds_time_ = refresh_feeds_time;
    }

    static void setIsProxyConnectionEnabled(const bool is_proxy_connection_enabled)
    {
        is_proxy_connection_enabled_ = is_proxy_connection_enabled;
    }

    static void setProxyIpAddress (const QString & proxy_ip_address)
    {
        proxy_ip_address_ = proxy_ip_address;
    }

    static void setProxyPort (const QString & proxy_port)
    {
        proxy_port_ = proxy_port;
    }

    static void setIsFilteringEnabled (const bool is_filtering_enabled)
    {
        is_filtering_enabled_ = is_filtering_enabled;
    }

public:
    static void loadSettings();
    static void saveSettings ();
    static void setProxySettings ();

private:
    Settings();
    virtual ~Settings ();

private:
    const static QString        filename_;
    static bool                 is_filtering_enabled_;
    static bool                 is_notifications_enabled_;
    static bool                 is_proxy_connection_enabled_;
    static QString              proxy_ip_address_;
    static QString              proxy_port_;
    static unsigned int         refresh_feeds_time_;

    static QString extractLineData (int index, const QString &line);
    static bool isSettingsDataValid (const int expected_length,
                             const QString &line,
                             const QString &error_message);
    static bool loadFiltersCheckBoxData (QTextStream &textStream);
    static bool loadNotificationsCheckBoxData (QTextStream &textStream);
    static bool loadProxyCheckBoxData (QTextStream &textStream);
    static QString loadProxyPort (QTextStream &textStream);
    static QString loadProxyServerAddress (QTextStream &textStream);
    static int loadRefreshTime (QTextStream &textStream);
    static void saveFiltersSettings (QTextStream & out);
    static void saveNotificationsSettings (QTextStream & out);
    static void saveProxySettings (QTextStream & out);
};

} //namespace Jelyazka

#endif // SETTINGS_H
