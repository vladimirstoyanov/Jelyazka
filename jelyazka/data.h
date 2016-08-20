#ifndef DATA_H
#define DATA_H
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/range/size_type.hpp>
#include "rssdata.h"
#include "rssarticle.h"

class Data: public RSSData
{
public:
    Data();
    RSSData *at(unsigned int index);
    boost::ptr_vector<RSSData>::size_type size();
    void pushBack(RSSData *rss_data);
    void erase(int index);
private:
     boost::ptr_vector<RSSData> rss_data_vector_;
};

#endif // DATA_H
