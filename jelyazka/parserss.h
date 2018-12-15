#ifndef PARSERSS_H
#define PARSERSS_H

#include <limits.h>

#include <QString.h>

#include "data.h"
#include "rssarticle.h"
#include "search.h"

class ParseRSS
{
public:
    ParseRSS(Data *data_tmp);
    //ToDo: create destructor

    void convert_string (QString &str, bool link); //ToDo: rename this function
    void findFeedDataRSS(int &index, QString content, RSSArticle &ar);
    void findFeedDataRDF(int &index, QString content, RSSArticle &ar);

public:
    int getArticlesFromRDFContent(QString content, RSSData *data);
    int getArticlesFromRSSContent(QString content, RSSData *data);
    int getContent(int item_b_index, int item_e_index, QString &description, QString content);
    int getDescription(int item_b_index, int item_e_index, QString &description, QString content);
    int getTextBetweenIndexes(int item_b_index,
                              int item_e_index,
                              QString begin_text,
                              QString end_text,
                              QString &text,
                              QString content);

    QString convert_entitie(QString entitie); //ToDO: rename this function
    QString returnURL(QString source, int index);

private:
    Data *data_;
};

#endif // PARSERSS_H
