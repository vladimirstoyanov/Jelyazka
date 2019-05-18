#include <QDebug.h>

#include "data.h"

Data::Data()
{

}

std::shared_ptr<RSSData> Data::at(const unsigned int index)
{
    //FIXME: unsafe method. If rss_data_vector_ is an empty one, then it will crash
    if (rss_data_vector_.size()<=index)
    {
        qDebug()<<"Data::at rss_data_vector_.size()<=index "<<index;
        //prevent crash
        return rss_data_vector_[0];
    }
    return rss_data_vector_[index];
}

void Data::pushBack(std::shared_ptr<RSSData> rss_data)
{
    rss_data_vector_.push_back(rss_data);
}

void Data::erase(int index)
{
    rss_data_vector_.erase(rss_data_vector_.begin() + index);
}

unsigned int Data::size()
{
    return rss_data_vector_.size();
}

