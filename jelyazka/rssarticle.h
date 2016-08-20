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
    void setTitle(QString title);
    void setLink(QString link);
    void setText(QString text);
    void setDate(QString date);
private:
    QString title_;
    QString link_;
    QString text_;
    QString date_;
};

#endif // RSSARTICLE_H
