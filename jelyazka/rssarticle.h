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
    //set
    void setTitle(QString title);
    void setLink(QString link);
    void setText(QString text);

private:
    QString title;
    QString link;
    QString text;
};

#endif // RSSARTICLE_H
