#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>

#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

namespace Jelyazka
{

class Settings
{
public:
    Settings();
    ~Settings ();

    //get methods
    static std::vector<QString> getCollectionFeeds ()
    {
        return collection_feeds_;
    }

    static std::vector<QString> getFavoriteFeeds ()
    {
        return favorite_feeds_;
    }

    static std::vector<QString> getFilters ()
    {
        return filters_;
    }

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

    //set methodss
    static void setCollectionFeeds (std::vector<QString> const & collection_feeds)
    {
        collection_feeds_.clear();
        for (unsigned int i=0; i<collection_feeds.size(); i++)
        {
            collection_feeds_.push_back(collection_feeds[i]);
        }
    }

    static void setFavoriteFeeds (std::vector<QString> const &favorite_feeds )
    {
        favorite_feeds_.clear();
        for (unsigned int i=0; i<favorite_feeds.size(); i++)
        {
            favorite_feeds_.push_back(favorite_feeds[i]);
        }
    }

    static void setFilters (std::vector<QString>  const & filters)
    {
        filters_.clear();
        for (unsigned int i=0; i<filters.size(); i++)
        {
            favorite_feeds_.push_back(filters[i]);
        }
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



private:
    static std::vector<QString> collection_feeds_;
    static std::vector<QString> favorite_feeds_;
    static std::vector<QString> filters_;
    static bool                 is_filtering_enabled_;
    static bool                 is_notifications_enabled_;
    static bool                 is_proxy_connection_enabled_;
    static QString              proxy_ip_address_;
    static QString              proxy_port_;
    static unsigned int         refresh_feeds_time_;

private:
    static void loadSettings();
    static void saveSettings ();
};

} //namespace Jelyazka

#endif // SETTINGS_H
