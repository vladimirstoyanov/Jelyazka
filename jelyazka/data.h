#ifndef DATA_H
#define DATA_H

//#include <boost/ptr_container/ptr_vector.hpp>
//#include <boost/range/size_type.hpp>
#include <vector>

#include "rssarticle.h"
#include "rssdata.h"


class Data: public RSSData
{
public:
    Data();
    //ToDo: create destructor that removes rss_data_vector_
    RSSData *at(unsigned int index);

    void erase(int index);
    void pushBack(RSSData *rss_data);
    //boost::ptr_vector<RSSData>::size_type size();
    unsigned int size();

private:
     //boost::ptr_vector<RSSData> rss_data_vector_;
    std::vector<RSSData*> rss_data_vector_;
};

#endif // DATA_H
