#ifndef DATA_H
#define DATA_H

#include <memory>
#include <vector>

#include "RSS/rssarticle.h"
#include "RSS/rssdata.h"


class Data: public RSSData
{
public:
    Data();
    std::shared_ptr<RSSData> at(const unsigned int index);

    void erase(int index);
    void pushBack(std::shared_ptr<RSSData> rss_data);
    unsigned int size();

private:
    std::vector<std::shared_ptr<RSSData>> rss_data_vector_;
};

#endif // DATA_H
