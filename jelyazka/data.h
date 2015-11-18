#ifndef DATA_H
#define DATA_H
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/range/size_type.hpp>
#include "rssdata.h"
#include "rssarticle.h"

class Data
{
public:
    Data();
    RSSData *at(int index);
    boost::ptr_vector<RSSData>::size_type size();
    void push_back(RSSData *rssData);
    void erase(int index);
private:
     boost::ptr_vector<RSSData> s_struct;

};

#endif // DATA_H
