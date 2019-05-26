#ifndef RSSARTICLE_H
#define RSSARTICLE_H

#include <QString>

class RSSArticle
{
public:
    RSSArticle();

    void setTitle(QString title);
    void setLink(QString link);
    void setText(QString text);
    void setDate(QString date);

public:
    QString getTitle();
    QString getLink();
    QString getText();
    QString getDate();

private:
    QString date_;
    QString link_;
    QString text_;
    QString title_;
};

#endif // RSSARTICLE_H
