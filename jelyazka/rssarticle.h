#ifndef RSSARTICLE_H
#define RSSARTICLE_H

#include <QString>

class RSSArticle
{
public:
    RSSArticle();

    //get
    QString getTitle();
    QString getLink();
    QString getText();
    QString getDate();

    //set
    void setTitle(QString title_);
    void setLink(QString link_);
    void setText(QString text_);
    void setDate(QString date_);
private:
    QString title;
    QString link;
    QString text;
    QString date;
};

#endif // RSSARTICLE_H
