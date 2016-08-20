#include "data.h"
#include <QDebug.h>
Data::Data()
{

}

RSSData*Data::at(int index)
{
    if (rss_data_vector_.size()<=index)
        qDebug()<<"Data::at rss_data_vector_.size()<=index "<<index;
    return &rss_data_vector_[index];
}

void Data::pushBack(RSSData *rss_data)
{
    rss_data_vector_.push_back(rss_data);
}

void Data::erase(int index)
{
    rss_data_vector_.erase(rss_data_vector_.begin() + index);
}

 boost::ptr_vector<RSSData>::size_type Data::size()
{
    return rss_data_vector_.size();
}

