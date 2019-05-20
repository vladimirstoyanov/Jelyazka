#ifndef PARSERSS_H
#define PARSERSS_H

#include <limits.h>
#include <memory>

#include <QString>
#include <QtDebug>

#include "data.h"
#include "rssarticle.h"
#include "search.h"

//ToDo: refactor this class
class ParseRSS
{
public:
    ParseRSS(std::shared_ptr<Data> data_tmp); //ToDo: remove this constructor
    ParseRSS();

    //ToDo: create destructor
    void convert_string (QString &str, const bool link); //ToDo: rename this function
    void findFeedDataRSS(int &index, const QString &content, RSSArticle &ar);
    void findFeedDataRDF(int &index, const QString &content, RSSArticle &ar);

public:
    int  getArticlesFromRDFContent(const QString &web_source, std::shared_ptr<RSSData> data); //ToDo: rename this function and make it privete
    int  getArticlesFromRSSContent(const QString &web_source, std::shared_ptr<RSSData> data); //ToDo: rename this function and make it privete
    int  getContent(const int item_b_index, const int item_e_index, QString &description, const QString &web_source);
    int  getDescription(const int item_b_index, const int item_e_index, QString &description, const QString &web_source);
    void getRSSDataByWebSource (const QString &web_source, std::shared_ptr<RSSData> data);
    int  getTextBetweenIndexes(const int item_b_index,
                               const int item_e_index,
                               const QString &begin_text,
                               const QString &end_text,
                               QString &text,
                               const QString &content);

    QString convert_entitie(const QString &entitie); //ToDo: rename this function
    QString returnURL(const QString &source, int index);

private:
    std::shared_ptr<Data> data_; //ToDo: remove this member

    int     checkWebSourceForRSSContent (const QString &web_source, QString &title, int &version);
    QString getEncodingByWebSource  (const QString &web_content);
    void    getStoryTag (const QString &web_content, QString &storyOpenTag, QString &storyEndTag);
};

#endif // PARSERSS_H
