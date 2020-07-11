#ifndef RSSARTICLE_H
#define RSSARTICLE_H

#include <QString>

class RSSArticle
{
public:
    RSSArticle();

    void setTitle(const QString &title);
    void setLink(const QString &link);
    void setText(const QString &text);
    void setDate(const QString &date);

public:
    QString getTitle() const;
    QString getLink() const;
    QString getText() const;
    QString getDate() const;

private:
    QString date_;
    QString link_;
    QString text_;
    QString title_;
};

#endif // RSSARTICLE_H
