#include "rssdata.h"

RSSData::RSSData()
{

}


//get
QString RSSData::getType ()
{
    return type;
}

QString RSSData::getSiteName()
{
    return site_name;
}

QString RSSData::getURL()
{
    return url;
}

QString RSSData::getEncoding()
{
    return encoding;
}

QString RSSData::getVersion()
{
    return version;
}

bool RSSData::getIsRead()
{
    return isRead;
}

bool RSSData::getIsLoaded()
{
    return isLoaded;
}

//set
void RSSData::setType(QString type_tmp)
{
    type = type_tmp;
}

void RSSData::setSiteName(QString site_name_tmp)
{
    site_name = site_name_tmp;
}

void RSSData::setURL(QString url_tmp)
{
    url = url_tmp;
}

void RSSData::setEncoding(QString enconding_tmp)
{
    encoding = enconding_tmp;
}

void RSSData::setVersion(QString version_tmp)
{
    version = version_tmp;
}

void RSSData::setIsRead(bool isRead_tmp)
{
    isRead = isRead_tmp;
}

void RSSData::setIsLoaded(bool isLoaded_tmp)
{
    isLoaded = isLoaded_tmp;
}
