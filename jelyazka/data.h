#ifndef DATA_H
#define DATA_H

#include <memory>
#include <vector>

#include "rssarticle.h"
#include "rssdata.h"


class Data: public RSSData
{
public:
    Data();
    //ToDo: create destructor that removes rss_data_vector_
    std::shared_ptr<RSSData> at(const unsigned int index);

    void erase(int index);
    void pushBack(std::shared_ptr<RSSData> rss_data);
    //boost::ptr_vector<RSSData>::size_type size();
    unsigned int size();

private:
     //boost::ptr_vector<RSSData> rss_data_vector_;
    std::vector<std::shared_ptr<RSSData>> rss_data_vector_;
};

#endif // DATA_H
