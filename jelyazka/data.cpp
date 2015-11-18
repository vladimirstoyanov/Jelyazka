#include "data.h"
#include <QDebug.h>
Data::Data()
{

}

RSSData*Data::at(int index)
{
    if (s_struct.size()<=index)
        qDebug()<<"Data::at s_struct.size()<=index "<<index;
    return &s_struct[index];
}

void Data::push_back(RSSData *rssData)
{
    s_struct.push_back(rssData);
}

void Data::erase(int index)
{
    s_struct.erase(s_struct.begin() + index);
}

 boost::ptr_vector<RSSData>::size_type Data::size()
{
    return s_struct.size();
}

