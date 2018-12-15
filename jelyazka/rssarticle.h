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
    bool getIsMarkedForRemove();

    //set
    void setTitle(QString title);
    void setLink(QString link);
    void setText(QString text);
    void setDate(QString date);
    void setIsMarkedForRemove (bool is_marked_for_remove);
private:
    QString title_;
    QString link_;
    QString text_;
    QString date_;
    bool is_marked_for_remove_;
};

#endif // RSSARTICLE_H
