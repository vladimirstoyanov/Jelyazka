#ifndef PARSERSS_H
#define PARSERSS_H

#include <QString.h>
#include <limits.h>
#include "rssarticle.h"
#include "search.h"
#include "data.h"

class ParseRSS
{
public:
    ParseRSS(Data *data_tmp);

    void findFeedDataRSS(int &index, QString content, RSSArticle &ar);
    void findFeedDataRDF(int &index, QString content, RSSArticle &ar);
    int getArticlesFromRSSContent(QString content, RSSData *data);
    int getArticlesFromRDFContent(QString content, RSSData *data);
    void convert_string (QString &str, bool link);
private:
    int getDescription(int item_b_index, int item_e_index, QString &description, QString content);
    int getTextBetweenIndexes(int item_b_index, int item_e_index, QString begin_text, QString end_text, QString &text, QString content);
    QString returnURL(QString source, int index);
    int getContent(int item_b_index, int item_e_index, QString &description, QString content);
    QString convert_entitie(QString entitie);
    Data *data;
};

#endif // PARSERSS_H