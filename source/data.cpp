//#include <QDebug.h>

#include "data.h"

Data::Data()
{

}

std::shared_ptr<RSSData> Data::at(const unsigned int index)
{
    std::shared_ptr <RSSData> rss_data = std::make_shared<RSSData> ();
    return rss_data;
}

void Data::pushBack(std::shared_ptr<RSSData> rss_data)
{
    //rss_data_vector_.push_back(rss_data);
}

void Data::erase(int index)
{
    //rss_data_vector_.erase(rss_data_vector_.begin() + index);
}

unsigned int Data::size()
{
    //return rss_data_vector_.size();
    return 0;
}

